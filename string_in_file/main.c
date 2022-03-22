/*
finds string ocurrences in file and optionally adds string after them
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winbase.h>

// uses CopyFile() therefore only works on windows

size_t fstrcpy(char** dest, const char* src_path);
size_t finsert(FILE** file, const char* fname, const char* mode,
               const char* buffer);

int main(int argv, char** argc) {
  if (argv < 3) {
    printf("usage: find [input] [findstring] optional:[output] [addstring]\n \
    input: file to search in\n \
    findstring: file containing string to be searched\n \
    output: output filename\n \
    addstring: file containing string to be added\n");
    return 0;
  }

  if (!CopyFile(argc[1], argc[3], FALSE)) {
    printf("COPYFILE FAILED; ABORTING\n");
    return 1;
  }

  // input file
  const char* fin_name = argc[3];
  const char* fin_mode = "r+";
  FILE* fin = fopen(fin_name, fin_mode);
  char str[64];
  char* addtxt = NULL;

  // file error handling
  if (fin == NULL) {
    printf("error opening file\n");
    return 1;
  }

  // optional argument - add text
  if (argc[4] != NULL) {
    if (fstrcpy(&addtxt, argc[4])) {
      printf("error copying add-string\n");
      return 1;
    }
  }

  // malloc search string
  char* search_str = NULL;
  if (fstrcpy(&search_str, argc[2])) {
    printf("error copying search-string\n");
    return 1;
  }

  printf("STRING TO SEARCH IN FILE: \n%s\n--------------\n", search_str);

  // search string in file
  int line = 0;
  int count = 0;

  size_t first_line_len = strcspn(search_str, "\r\n");
  char* first_line = calloc(sizeof(char), first_line_len + 1);
  strncpy(first_line, search_str, first_line_len);

  // read file until newline or 64 bytes
  while (fgets(str, 64, fin) != NULL) {
    // check for first line of search string
    if (strstr(str, first_line) != 0) {
      // remember position
      long pos = ftell(fin);

      // got a match for the first line
      // copy a string the same length as the search string and compare it
      char* buf = calloc(sizeof(char), strlen(search_str));
      strcpy(buf, str);

      size_t i;
      for (i = strlen(buf); i < strlen(search_str); i++) {
        buf[i] = fgetc(fin);
      }
      buf[i] = '\0';

      if (!strcmp(search_str, buf)) {
        // found it
        printf("found string in line: %d\n", line + 1);
        count++;

        if (addtxt != NULL) {
          if (finsert(&fin, fin_name, fin_mode, addtxt)) {
            printf("INSERTION FAILED\n");
            return 1;
          }

          printf("wrote string after last match\n");
        }
      }
      fseek(fin, pos, SEEK_SET);
    }

    line++;
  }

  printf("found %d times\n", count);

  fclose(fin);
  
  // malloc'd inside fstrcpy()
  free(search_str);
  if (addtxt != NULL) {
    free(addtxt);
  }

  return 0;
}

// copies file contents to mallocd string
// remember to free
size_t fstrcpy(char** dest, const char* src_path) {
  FILE* src = fopen(src_path, "r");

  if (src == NULL || dest == NULL) {
    return 1;
  }

  fseek(src, 0L, SEEK_END);

  // file end pos = file size
  long sz = ftell(src);

  rewind(src);

  *dest = malloc(sizeof(char) * sz);

  if (*dest == NULL) {
    return 1;
  }

  // remember *dest
  char* tmp = *dest;

  char c;
  while ((c = fgetc(src)) != EOF) {
    // char** IS NOT an array, therefore i CANT *dest[i]
    **dest = c;
    // pointer arithmetic increments pointer to next char
    (*dest)++;
  }
  // null terminator
  **dest = '\0';

  // decrement pointer back
  *dest = tmp;

  fclose(src);

  return 0;
}

// DESTRUCTIVE FUNCTION WILL DELETE INPUT FILE
// insertion is not real so a copy must be created
size_t finsert(FILE** fptr, const char* fname, const char* mode,
               const char* buffer) {
  const char* tmpname = "tmp";
  FILE* f2 = fopen(tmpname, "w+"); // new file
  FILE* file = *fptr; // old file
  char c;
  char str[64];
  
  // remember file position
  long offset = ftell(file);

  fseek(file, 0, SEEK_SET);

  // copy file up to the insertion point
  while (ftell(file) != offset) {
    c = fgetc(file);
    fputc(c, f2);
  }

  // write the new text
  fprintf(f2, "%s", buffer);

  // remember file position
  long offset_insert = ftell(f2);

  // copy the rest of the file
  while ((c = fgetc(file)) != EOF) {
    fputc(c, f2);
  }

  // delete first file, rename second file to first one
  fclose(file);
  if (remove(fname)) {
    return 1;
  }
  fclose(f2);
  if (rename(tmpname, fname)) {
    return 1;
  }

  file = fopen(fname, mode);

  // go back to insertion position
  fseek(file, offset_insert, SEEK_SET);

  return 0;
}
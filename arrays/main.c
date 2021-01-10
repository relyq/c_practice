#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/*
void testpush(void);
void testpop(void);
*/

int main(void) {
  printf("hewwo world uwu\n");
  vector v = vector_create(8);

  for (int i = 0; i < 15; i++) vector_push(&v, 0xff);
  vector_prepend(&v, 0x3f);
  vector_insert(&v, 10, 0x7f);
  vector_insert(&v, 10, 0x7f);
  vector_prepend(&v, 0x3f);

  printf("v capacity:\t %d\n", vector_capacity(&v));
  printf("v size:\t\t %d\n", vector_size(&v));
  printf("v isempty:\t %d\n\n", vector_isEmpty(&v));

  for (int i = 0; i < vector_capacity(&v); i++) {
    printf("v[%d]:\t\t %d\n", i, vector_at(&v, i));
  }

  vector_remove(&v, 0xff);
  vector_push(&v, 0x3f);

  printf("\n");

  for (int i = 0; i < vector_capacity(&v); i++) {
    printf("v[%d]:\t\t %d\n", i, vector_at(&v, i));
  }
  printf("v size:\t\t %d\n", vector_size(&v));

  printf("vfind0xff:\t %d\n", vector_find(&v, 0xff));

  vector_destroy(&v);
  return 0;
}
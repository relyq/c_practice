#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int vector_test_createdestroy(void);
int vector_test_pushpop(void);
int vector_test_at(void);
int vector_test_insertdelete(void);
int vector_test_findremove(void);
void vector_print(vector* v);

int main(void) {
  int errors = 0;
  int errorcode;
  if (!(errorcode = vector_test_createdestroy())) {
    printf("vector creation & destruction test finished OK\n");
  } else {
    printf("vector creation & destruction test finished with ERROR CODE: %#x\n",
           errorcode);
    errors |= 0x01;
  }

  if (!(errorcode = vector_test_pushpop())) {
    printf("vector push & pop test finished OK\n");
  } else {
    printf("vector push & pop test finished with ERROR CODE: %#x\n", errorcode);
    errors |= 0x02;
  }

  if (!(errorcode = vector_test_at())) {
    printf("vector 'at' test finished OK\n");
  } else {
    printf("vector 'at' test finished with ERROR CODE: %#x\n", errorcode);
    errors |= 0x04;
  }

  if (!(errorcode = vector_test_insertdelete())) {
    printf("vector insert & delete test finished OK\n");
  } else {
    printf("vector insert & delete test finished with ERROR CODE: %#x\n",
           errorcode);
    errors |= 0x08;
  }

  if (!(errorcode = vector_test_findremove())) {
    printf("vector find & remove test finished OK\n");
  } else {
    printf("vector find & remove test finished with ERROR CODE: %#x\n",
           errorcode);
    errors |= 0x10;
  }

  if (!errors) {
    printf("all tests finished without errors\n");
  } else {
    printf("tests finished with error code: %#x\n", errors);
  }

  return 0;
}

int vector_test_createdestroy(void) {
  int error = 0;
  vector v[8];
  v[0] = vector_create(0);
  v[1] = vector_create(8);
  v[2] = vector_create(25);
  v[3] = vector_create(45);
  v[4] = vector_create(125);
  v[5] = vector_create(245);
  v[6] = vector_create(445);
  v[7] = vector_create(-0xff);

  if (v[0].capacity != 0) {
    printf(
        "ERROR: vector with size of 0 should be created with capacity of 0\n");
    error |= 0x01;
  }
  if (v[1].capacity != 16) {
    printf(
        "ERROR: vector with size smaller than 16 should be created with "
        "capacity of 16\n");
    error |= 0x02;
  }
  if (v[2].capacity != 32) {
    printf(
        "ERROR: vector with size 16 < x < 32 should be created with capacity "
        "of 32\n");
    error |= 0x04;
  }
  if (v[3].capacity != 64) {
    printf(
        "ERROR: vector with size 32 < x < 64 should be created with capacity "
        "of 64\n");
    error |= 0x08;
  }
  if (v[4].capacity != 128) {
    printf(
        "ERROR: vector with size 64 < x < 128 should be created with capacity "
        "of 128\n");
    error |= 0x10;
  }
  if (v[5].capacity != 256) {
    printf(
        "ERROR: vector with size 128 < x < 256 should be created with capacity "
        "of 256\n");
    error |= 0x20;
  }
  if (v[6].capacity != 512) {
    printf(
        "ERROR: vector with size 256 < x < 512 should be created with capacity "
        "of 512\n");
    error |= 0x40;
  }
  if (v[7].capacity != 0) {
    printf(
        "ERROR: vector with negative size should be created with capacity of "
        "0\n");
    error |= 0x80;
  }

  for (int i = 0; i < 8; i++) {
    vector_destroy(&v[i]);
    if (v[i].p != NULL || v[i].capacity != 0 || v[i].size != 0) {
      printf("ERROR: vector memory has not been freed corretly\n");
      printf("INFO: v[%d].p = %#x\n", i, v[i].p);
      printf("INFO: v[%d].capacity = %d\n", i, v[i].capacity);
      printf("INFO: v[%d].size = %d\n", i, v[i].size);
      error |= 0x100;
    }
  }

  return error;
}

int vector_test_pushpop(void) {
  int error = 0;
  vector v = vector_create(8);

  for (int i = 0; i < 17; i++) {
    vector_push(&v, i);
    if (*(v.p + i) != i) {
      printf("ERROR: pushed value is not right\n");
      error |= 0x01;
    }
  }
  if (v.capacity != 32) {
    printf("ERROR: vector was not resized when at full capacity after push\n");
    error |= 0x02;
  }
  if (v.size != 17) {
    printf("ERROR: vector size not correct after push\n");
    printf("INFO: v.size = %d\n", v.size);
    error |= 0x04;
  }

  for (int val, i = 17; i > 0; i--) {
    if (val = vector_pop(&v) != i - 1) {
      printf("ERROR: popped value is not right\n");
      printf("INFO: value popped at v[%d] = %d\n", i, val);
      error |= 0x08;
    }
  }

  if (v.capacity != 16) {
    printf(
        "ERROR: vector was not resized when at quarter capacity after pop\n");
    printf("INFO: v.capacity = %d\n", v.capacity);
    error |= 0x10;
  }

  if (v.size) {
    printf("ERROR: vector size not correct after pop\n");
    error |= 0x20;
  }

  if (vector_pop(&v) != 0) {
    printf("ERROR: popped value should be 0 when vector is empty\n");
    error |= 0x40;
  }

  vector_destroy(&v);
  return error;
}

int vector_test_at(void) {
  int error = 0;

  vector v = vector_create(16);
  for (int val, i = 0; i < 16; i++) {
    vector_push(&v, i);
    if (val = vector_at(&v, i) != i) {
      printf("ERROR: returned value not correct\n");
      printf("INFO: value returned at v[%d] = %d\n", i, val);
      error |= 0x01;
    }
  }

  if (vector_at(&v, vector_size(&v) + 1) != -1) {
    printf("ERROR 0x02: vector_at() should return -1 when out of bounds\n");
    error |= 0x02;
  }
  if (vector_at(&v, -1) != -1) {
    printf("ERROR 0x04: vector_at() should return -1 when out of bounds\n");
    error |= 0x04;
  }

  vector_destroy(&v);

  return error;
}

int vector_test_insertdelete(void) {
  int error = 0;
  vector v = vector_create(16);

  for (int i = 0; i < 16; i++) {
    vector_push(&v, i);
  }

  vector_insert(&v, 7, 0xff);

  for (int val, i = 0; i < v.size; i++) {
    val = vector_at(&v, i);
    if (i == 7 && val != 0xff) {
      printf("ERROR: inserted value not correct\n");
      error |= 0x01;
    } else if (i < 7 && val != i) {
      printf("ERROR: leading items were modified after insert\n");
      error |= 0x02;
    } else if (i > 7 && val != i - 1) {
      printf("ERROR: trailing items not right after insert\n");
      printf("INFO: value at v[%d] = %d\n", i, val);
      error |= 0x04;
    }
  }

  if (v.size != 17) {
    printf("ERROR: inserting item should increment size\n");
    error |= 0x08;
  }

  if (v.capacity != 32) {
    printf(
        "ERROR: inserting item when capacity is full should resize vector\n");
    error |= 0x10;
  }

  if (vector_insert(&v, -1, 0xff) != -1) {
    printf(
        "ERROR 0x20: inserting item out of bounds should return error code "
        "-1\n");
    error |= 0x20;
  }

  if (vector_insert(&v, 0x6f, 0xff) != -1) {
    printf(
        "ERROR 0x40: inserting item out of bounds should return error code "
        "-1\n");
    error |= 0x40;
  }

  vector_delete(&v, 7);

  for (int val, i = 0; i < v.size; i++) {
    val = vector_at(&v, i);
    if (i < 7 && val != i) {
      printf("ERROR: leading items were modified after delete\n");
      error |= 0x80;
    } else if (i >= 7 && val != i) {
      printf("ERROR: trailing items not right after delete\n");
      printf("INFO: value at v[%d] = %d\n", i, val);
      error |= 0x100;
    }
  }

  if (v.size != 16) {
    printf("ERROR: deleting item should increment size\n");
    error |= 0x200;
  }

  if (vector_delete(&v, -1) != -1) {
    printf(
        "ERROR: deleting item out of bounds should return error code "
        "-1\n");
    error |= 0x400;
  }

  while (v.size) {
    vector_delete(&v, 0);
  }

  if (v.capacity != 16) {
    printf(
        "ERROR: deleting item when size is a quarter capacity should resize "
        "vector\n");
    error |= 0x800;
  }

  vector_destroy(&v);
  return error;
}

int vector_test_findremove(void) {
  int error = 0;
  vector v = vector_create(16);

  for (int i = 0; i < 16; i++) {
    vector_push(&v, i);
  }

  *(v.p + 7) = 0xff;

  if (vector_find(&v, 0xff) != 7) {
    printf("ERROR: vector_find() failed\n");
    error |= 0x01;
  }

  if (vector_find(&v, 0xffff) != -1) {
    printf("ERROR: vector_find() should return -1 when value is not found\n");
    error |= 0x02;
  }

  int val;

  if ((val = vector_remove(&v, 0xff)) != 1) {
    printf(
        "ERROR: vector_remove() did not correctly return the number of items "
        "removed\n");
    printf("INFO: returned value: %d\n", val);
    error |= 0x04;
  }

  if (vector_remove(&v, 0xff)) {
    printf("ERROR: vector_remove() should return 0 if no items were removed\n");
    error |= 0x08;
  }

  if (vector_at(&v, 7) != 8) {
    printf("ERROR: vector_remove() did not remove the item correctly\n");
    error |= 0x10;
  }

  vector_destroy(&v);
  return error;
}

void vector_print(vector* v) {
  for (int i = 0; i < v->size; i++) {
    printf("%d\t", vector_at(v, i));
    if (!(i % 4)) printf("\n");
  }
  printf("\n\n");
}
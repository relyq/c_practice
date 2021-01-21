#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector {
  size_t capacity;
  size_t size;
  int* p;
} vector;

vector vector_create(size_t vsize);
void vector_destroy(vector* v);
int vector_size(const vector* v);
int vector_capacity(const vector* v);
int vector_isEmpty(const vector* v);
int vector_at(const vector* v, const size_t index);
void vector_push(vector* v, const int item);
int vector_pop(vector* v);
int vector_insert(vector* v, const size_t index, int item);
void vector_prepend(vector* v, const int item);
int vector_delete(vector* v, const size_t index);
int vector_remove(vector* v, const int item);
int vector_find(vector* v, const int item);
int vector_update(vector *v, const size_t index, int item);

#endif

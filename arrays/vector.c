#include "vector.h"

#include <stdlib.h>

// private methods

void vector_resize(vector* v, size_t new_size) {
  int* new_ptr = realloc(v->p, new_size * (int)sizeof(int));
  if (new_ptr) {
    v->p = new_ptr;
    v->capacity = new_size;
  }  // realloc can fail
}

// public methods

vector vector_create(size_t vsize) {
  vector v;
  v.size = 0;
  if (vsize < 1) {
    v.p = NULL;
    v.capacity = 0;
  } else if (vsize < 16) {
    v.p = (int*)malloc(16 * sizeof(int));
    v.capacity = 16;
  } else {
    v.p = (int*)malloc(vsize * sizeof(int));
    v.capacity = vsize;
  }
  return v;
}

int vector_size(const vector* v) { return v->size; }

int vector_capacity(const vector* v) { return v->capacity; }

int vector_isEmpty(const vector* v) { return v->size ? 0 : 1; }

int vector_at(const vector* v, const int index) {
  if (index < v->capacity) return *(v->p + index);
  return -1;  // out of bounds error
}

void vector_push(vector* v, const int item) {
  if (v->size == v->capacity) vector_resize(v, v->capacity * 2);
  *(v->p + v->size) = item;
  v->size++;
}

int vector_pop(vector* v) {
  if (v->size == v->capacity / 4) vector_resize(v, v->capacity / 2);
  int last_item = vector_at(v, v->size - 1);
  v->size--;
  return last_item;
}

void vector_insert(vector* v, const int index, int item) {
  if (v->size == v->capacity) vector_resize(v, v->capacity * 2);
  v->size++;
  int tmp;
  for (int i = 0; i < v->size - index; i++) {
    tmp = vector_at(v, index + i);
    *(v->p + index + i) = item;
    item = tmp;
  }
}

void vector_prepend(vector* v, const int item) { vector_insert(v, 0, item); }

void vector_delete(vector* v, const int index) {
  if (v->size == v->capacity / 4) vector_resize(v, v->capacity / 2);
  int tmp;
  v->size--;
  for (int i = 0; i < v->size - index; i++) {
    tmp = vector_at(v, index + i + 1);
    *(v->p + index + i) = tmp;
    *(v->p + index + i + 1) = 0;
  }
}

void vector_remove(vector* v, const int item) {
  for (int i = 0; i < v->size; i++) {
    if (vector_at(v, i) == item) {
      vector_delete(v, i);
      i--;
    }
  }
}

int vector_find(vector* v, const int item) {
  for (int i = 0; i < v->size; i++) {
    if (vector_at(v, i) == item) return i;
  }
  return -1;
}

void vector_destroy(vector* v) {
  free(v->p);
  v->capacity = 0;
}
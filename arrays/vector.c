#include "vector.h"

#include <stdlib.h>

// private methods

static void vector_resize(vector* v, size_t new_size) {
  if (new_size < 1)
    return;
  else if (new_size < 16)
    new_size = 16;
  else {
    unsigned int size_tmp = new_size;
    // size rounded up to next power of two
    size_tmp--;
    size_tmp |= size_tmp >> 1;
    size_tmp |= size_tmp >> 2;
    size_tmp |= size_tmp >> 4;
    size_tmp |= size_tmp >> 8;
    size_tmp |= size_tmp >> 16;
    size_tmp++;

    new_size = size_tmp;
  }
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
    unsigned int size_tmp = vsize;
    // size rounded up to next power of two
    size_tmp--;
    size_tmp |= size_tmp >> 1;
    size_tmp |= size_tmp >> 2;
    size_tmp |= size_tmp >> 4;
    size_tmp |= size_tmp >> 8;
    size_tmp |= size_tmp >> 16;
    size_tmp++;

    vsize = size_tmp;

    v.p = (int*)malloc(vsize * sizeof(int));
    v.capacity = vsize;
  }
  return v;
}

int vector_size(const vector* v) { return v->size; }

int vector_capacity(const vector* v) { return v->capacity; }

int vector_isEmpty(const vector* v) { return v->size ? 0 : 1; }

int vector_at(const vector* v, const size_t index) {
  if (index < 0 || index > v->size) return -1;  // out of bounds error
  return *(v->p + index);
}

void vector_push(vector* v, const int item) {
  if (v->size == v->capacity) vector_resize(v, v->capacity * 2);
  *(v->p + v->size) = item;
  v->size++;
}

int vector_pop(vector* v) {
  if (!v->size) return 0;
  if ((v->size == v->capacity / 4) && (v->capacity > 16))
    vector_resize(v, v->capacity / 2);
  int last_item = *(v->p + v->size - 1);
  v->size--;
  return last_item;
}

int vector_insert(vector* v, const size_t index, int item) {
  if (index < 0 || index > v->size) return -1;
  if (v->size == v->capacity) vector_resize(v, v->capacity * 2);
  v->size++;
  int tmp;
  for (int i = 0; i < v->size - index; i++) {
    tmp = vector_at(v, index + i);
    *(v->p + index + i) = item;
    item = tmp;
  }

  return 0;
}

void vector_prepend(vector* v, const int item) { vector_insert(v, 0, item); }

int vector_delete(vector* v, const size_t index) {
  if (index < 0 || index > v->size) return -1;
  if (v->size == v->capacity / 4) vector_resize(v, v->capacity / 2);
  int tmp;
  v->size--;
  for (int i = 0; i < v->size - index; i++) {
    tmp = vector_at(v, index + i + 1);
    *(v->p + index + i) = tmp;
    *(v->p + index + i + 1) = 0;
  }

  return 0;
}

int vector_remove(vector* v, const int item) {
  int items_removed = 0;
  for (int i = 0; i < v->size; i++) {
    if (vector_at(v, i) == item) {
      vector_delete(v, i);
      i--;
      items_removed++;
    }
  }
  return items_removed;
}

int vector_find(vector* v, const int item) {
  for (int i = 0; i < v->size; i++) {
    if (vector_at(v, i) == item) return i;
  }
  return -1;
}

void vector_destroy(vector* v) {
  free(v->p);
  v->p = NULL;
  v->capacity = 0;
  v->size = 0;
}
#include "queue.h"

#include <stdlib.h>

// private methods

// public methods

queue queue_create() {
  queue q;
  q.list = malloc(sizeof(slist));
  *q.list = slist_create();
  q.size = 0;

  return q;
}

size_t queue_size(queue* q) { return q->size; }

int queue_empty(queue* q) { return q->size ? 0 : 1; }

int queue_front(queue* q) { return slist_at(q->list, 0); }

int queue_back(queue* q) { return slist_at(q->list, q->size - 1); }

int queue_push(queue* q, int item) {
  if (!q) return -1;
  slist_pushback(q->list, item);
  q->size++;

  return 0;
}

int queue_pop(queue* q) {
  if (!q) return -1;
  return slist_popfront(q->list);
}

void queue_destroy(queue* q) {
  slist_destroy(q->list);
  free(q->list);
  q->list = NULL;
  q->size = 0;
}
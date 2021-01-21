#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "slist_tail.h"

typedef struct queue {
  slist* list;
  size_t size;
} queue;

queue queue_create(void);
size_t queue_size(queue* q);
int queue_empty(queue* q);
int queue_front(queue* q);
int queue_back(queue* q);
int queue_push(queue* q, int item);
int queue_pop(queue* q);
void queue_destroy(queue* q);

#endif
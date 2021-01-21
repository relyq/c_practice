#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>

typedef struct sl_node {
  int item;
  struct sl_node* next;
} sl_node;

typedef struct slist {
  sl_node* head;
  size_t size;
} slist;

slist slist_create(void);
size_t slist_size(slist* l);
int slist_empty(slist* l);
int slist_front(slist* l);
int slist_back(slist* l);
int slist_at(slist* l, const size_t index);
int slist_insert(slist* l, const size_t index, int item);
int slist_pushfront(slist* l, int item);
int slist_popfront(slist* l);
int slist_pushback(slist* l, int item);
int slist_popback(slist* l);
int slist_delete(slist* l, const size_t index);
void slist_destroy(slist* l);
sl_node* slist_goto(sl_node* n, const size_t index);


#endif
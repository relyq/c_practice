#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct dl_node {
  int item;
  struct dl_node* next;
  struct dl_node* prev;
} dl_node;

typedef struct dlist {
  dl_node* head;
  size_t size;
} dlist;

dlist dlist_create(void);
size_t dlist_size(dlist* l);
int dlist_empty(dlist* l);
int dlist_front(dlist* l);
int dlist_back(dlist* l);
int dlist_at(dlist* l, const size_t index);
int dlist_insert(dlist* l, const size_t index, int item);
int dlist_pushfront(dlist* l, int item);
int dlist_popfront(dlist* l);
int dlist_pushback(dlist* l, int item);
int dlist_popback(dlist* l);
int dlist_delete(dlist* l, const size_t index);
void dlist_destroy(dlist* l);
dl_node* dlist_goto(dl_node* n, const size_t index);

#endif
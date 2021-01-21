#include "dlist.h"

#include <stdlib.h>

// private methods

dl_node* dlist_goto(dl_node* n, const size_t index) {
  if (!index)
    return n;
  else
    return dlist_goto(n->next, index - 1);
}

// public methods

dlist dlist_create(void) {
  dlist l;
  l.head = NULL;
  l.size = 0;

  return l;
}

int dlist_at(dlist* l, const size_t index) {
  if (index > l->size - 1 || !l->size) return -1;
  return dlist_goto(l->head, index)->item;
}

size_t dlist_size(dlist* l) { return l->size; }

int dlist_empty(dlist* l) { return l->size ? 0 : 1; }

int dlist_front(dlist* l) { return dlist_at(l, 0); }

int dlist_back(dlist* l) { return dlist_at(l, l->size - 1); }

int dlist_insert(dlist* l, const size_t index, int item) {
  if (index > l->size) return -1;
  dl_node* tmp = malloc(sizeof(dl_node));
  tmp->item = item;
  tmp->next = NULL;
  tmp->next = NULL;
  if (!index) {
    if (l->size) l->head->prev = tmp;
    tmp->next = l->head;
    tmp->prev = NULL;
    l->head = tmp;
  } else {
    dl_node* prev = dlist_goto(l->head, index - 1);
    tmp->next = prev->next;
    tmp->prev = prev;
    prev->next = tmp;
  }
  l->size++;

  return 0;
}

int dlist_delete(dlist* l, const size_t index) {
  if (index > l->size - 1 || !l->size) return -1;
  dl_node* tmp;      // node before the one to delete
  dl_node* byenode;  // node to delete
  if (!index) {
    byenode = l->head;
    l->head = byenode->next;
    free(byenode);
  } else {
    tmp = dlist_goto(l->head, index - 1);
    byenode = tmp->next;
    tmp->next = byenode->next;
    free(byenode);
  }
  l->size--;

  return 0;
}

int dlist_pushfront(dlist* l, int item) { return dlist_insert(l, 0, item); }

int dlist_popfront(dlist* l) {
  int val = dlist_at(l, 0);
  dlist_delete(l, 0);
  return val;
}

int dlist_pushback(dlist* l, int item) {
  return dlist_insert(l, l->size - 1, item);
}

int dlist_popback(dlist* l) {
  int val = dlist_at(l, l->size - 1);
  dlist_delete(l, l->size - 1);
  return val;
}

void dlist_destroy(dlist* l) {
  while (l->size) {
    dlist_delete(l, 0);
  }
}
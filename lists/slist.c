#include "slist.h"

#include <stdlib.h>

// private methods

sl_node* slist_goto(sl_node* n, const size_t index) {
  if (!n) return NULL;
  if (!index)
    return n;
  else
    return slist_goto(n->next, index - 1);
}

// public methods

slist slist_create(void) {
  slist l;
  l.head = NULL;
  l.size = 0;

  return l;
}

int slist_at(slist* l, const size_t index) {
  if (!l || index > l->size - 1 || !l->size) return -1;
  return slist_goto(l->head, index)->item;
}

size_t slist_size(slist* l) {
  if (!l) return -1;
  return l->size;
}

int slist_empty(slist* l) {
  if (!l) return -1;
  return l->size ? 0 : 1;
}

int slist_front(slist* l) {
  if (!l) return -1;
  return slist_at(l, 0);
}

int slist_back(slist* l) {
  if (!l) return -1;
  return slist_at(l, l->size - 1);
}

int slist_insert(slist* l, const size_t index, int item) {
  if (!l || index > l->size) return -1;

  sl_node* tmp = malloc(sizeof(sl_node));
  if (!tmp) return -1;

  tmp->item = item;

  if (!index) {
    tmp->next = l->head;
    l->head = tmp;
  } else {
    sl_node* prev = slist_goto(l->head, index - 1);
    tmp->next = prev->next;
    prev->next = tmp;
  }

  l->size++;

  return 0;
}

int slist_delete(slist* l, const size_t index) {
  if (!l || index > l->size - 1 || !l->size) return -1;

  sl_node* byenode;  // node to delete

  if (!index) {
    byenode = l->head;
    l->head = byenode->next;
    free(byenode);
  } else {
    sl_node* tmp;  // node before the one to delete
    tmp = slist_goto(l->head, index - 1);
    byenode = tmp->next;
    tmp->next = byenode->next;
    free(byenode);
  }

  l->size--;

  return 0;
}

int slist_pushfront(slist* l, int item) {
  if (!l) return -1;
  return slist_insert(l, 0, item);
}

int slist_popfront(slist* l) {
  if (!l || !l->size) return -1;

  int val = slist_at(l, 0);
  slist_delete(l, 0);
  return val;
}

int slist_pushback(slist* l, int item) {
  if (!l) return -1;
  return slist_insert(l, l->size - 1, item);
}

int slist_popback(slist* l) {
  if (!l || !l->size) return -1;
  int val = slist_at(l, l->size - 1);
  slist_delete(l, l->size - 1);
  return val;
}

int slist_destroy(slist* l) {
  if (!l) return -1;
  while (l->size) {
    slist_delete(l, 0);
  }
  return 0;
}

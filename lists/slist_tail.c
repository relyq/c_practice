#include "slist_tail.h"

#include <stdlib.h>

// private methods

sl_node* slist_goto(sl_node* n, const size_t index) {
  if (!n) return NULL;
  if (!index)
    return n;
  else
    return slist_goto(n->next, index - 1);
}

int slist_insertat(slist* l, sl_node* n, int item) {
  if (!l || !n) return -1;
  sl_node* tmp = malloc(sizeof(sl_node));
  tmp->item = item;
  tmp->next = n->next;
  n->next = tmp;
  l->tail = tmp;
  l->size++;
  return 0;
}

// public methods

slist slist_create(void) {
  slist l;
  l.head = NULL;
  l.tail = NULL;
  l.size = 0;

  return l;
}

int slist_at(slist* l, const size_t index) {
  if (index > l->size - 1 || !l->size) return -1;
  return slist_goto(l->head, index)->item;
}

size_t slist_size(slist* l) { return l->size; }

int slist_empty(slist* l) { return l->size ? 0 : 1; }

int slist_front(slist* l) { return slist_at(l, 0); }

int slist_back(slist* l) { return slist_at(l, l->size - 1); }

int slist_insert(slist* l, const size_t index, int item) {
  if (index > l->size || !l) return -1;
  sl_node* tmp = malloc(sizeof(sl_node));
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
  l->tail = slist_goto(l->head, l->size - 1);

  return 0;
}

int slist_delete(slist* l, const size_t index) {
  if (index > l->size - 1 || !l->size) return -1;
  sl_node* tmp;      // node before the one to delete
  sl_node* byenode;  // node to delete
  if (!index) {
    byenode = l->head;
    l->head = byenode->next;
    free(byenode);
  } else {
    tmp = slist_goto(l->head, index - 1);
    byenode = tmp->next;
    tmp->next = byenode->next;
    free(byenode);
  }
  l->size--;
  l->tail = slist_goto(l->head, l->size - 1);

  return 0;
}

int slist_pushfront(slist* l, int item) { return slist_insert(l, 0, item); }

int slist_popfront(slist* l) {
  int val = slist_at(l, 0);
  slist_delete(l, 0);
  return val;
}

int slist_pushback(slist* l, int item) {
  if (!l->size) return slist_insert(l, 0, item);
  return slist_insertat(l, l->tail, item);
}

int slist_popback(slist* l) {
  int val = slist_at(l, l->size - 1);
  slist_delete(l, l->size - 1);
  return val;
}

void slist_destroy(slist* l) {
  while (l->size) {
    slist_delete(l, 0);
  }
}

#include <stdio.h>

#include "dlist.h"
#include "slist.h"

void slist_print(slist* l);
void dlist_print(dlist* l);
void slist_dump(slist* l);
void dlist_dump(dlist* l);
void slist_test();
void dlist_test();


int main(void) {
  slist_test();
  dlist_test();
  return 0;
}

void slist_print(slist* l) {
  for (size_t i = 0; i < l->size; i++) {
    printf("%d\t", slist_at(l, i));
    if (!(i % 4)) printf("\n");
  }
  printf("\n\n");
}

void slist_dump(slist* l) {
  printf("&l: %p\tl.head: %p\tl.size: %ld\n", &l,l->head, l->size);
  for (size_t i = 0; i < l->size; i++) {
    int item = slist_at(l, i);
    sl_node* node = slist_goto(l->head, i);
    printf("l[%ld].item: %d\t&l[%ld]: %p\tl[%ld].next: %p\n", i, item, i, node,
           i, node->next);
  }
  printf("\n");
}

void dlist_print(dlist* l) {
  for (size_t i = 0; i < l->size; i++) {
    printf("%d\t", dlist_at(l, i));
    if (!(i % 4)) printf("\n");
  }
  printf("\n\n");
}

void dlist_dump(dlist* l) {
  printf("&l: %p\tl.head: %p\tl.size: %ld\n", &l,l->head, l->size);
  for (size_t i = 0; i < l->size; i++) {
    int item = dlist_at(l, i);
    dl_node* node = dlist_goto(l->head, i);
    printf("l[%ld].item: %d\t&l[%ld]: %p\tl[%ld].prev: %p\tl[%ld].next: %p\n",
           i, item, i, node, i, node->prev, i, node->next);
  }
  printf("\n");
}

void slist_test() {
  slist l = slist_create();
  for (int i = 7; i > -1; i--) {
    slist_pushfront(&l, i);
  }

  slist_pushback(&l, 0xff);

  slist_print(&l);

  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));

  printf("\n");
  slist_dump(&l);

  printf("popfront = %d\n", slist_popfront(&l));
  printf("popback = %d\n", slist_popback(&l));

  slist_print(&l);
  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));

  slist_destroy(&l);
  printf("\nsize: %ld\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));
}

void dlist_test() {
  dlist l = dlist_create();
  for (int i = 7; i > -1; i--) {
    dlist_pushfront(&l, i);
  }

  dlist_pushback(&l, 0xff);

  dlist_print(&l);

  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\n", dlist_size(&l),
         dlist_empty(&l), dlist_front(&l), dlist_back(&l));

  printf("\n");
  dlist_dump(&l);

  printf("popfront = %d\n", dlist_popfront(&l));
  printf("popback = %d\n", dlist_popback(&l));

  dlist_print(&l);
  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\n", dlist_size(&l),
         dlist_empty(&l), dlist_front(&l), dlist_back(&l));

  dlist_destroy(&l);
  printf("\nsize: %ld\nempty: %d\nfront: %d\nback: %d\n", dlist_size(&l),
         dlist_empty(&l), dlist_front(&l), dlist_back(&l));
}
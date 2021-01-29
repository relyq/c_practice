#include <stdio.h>

#include "slist.h"

void slist_print(slist* l);
void slist_dump(slist* l);
void slist_test();

int main(void) {
  printf("slist test\n");
  slist_test();
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
  printf("&l: %p\tl.head: %p\tl.size: %ld\n", &l, l->head, l->size);
  for (size_t i = 0; i < l->size; i++) {
    int item = slist_at(l, i);
    sl_node* node = slist_goto(l->head, i);
    printf("l[%ld].item: %d\t&l[%ld]: %p\tl[%ld].next: %p\n", i, item, i, node,
           i, node->next);
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

  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\nhead: %p\n",
         slist_size(&l), slist_empty(&l), slist_front(&l), slist_back(&l),
         l.head);

  printf("\n");
  slist_dump(&l);

  printf("popfront = %d\n", slist_popfront(&l));
  printf("popback = %d\n", slist_popback(&l));

  slist_print(&l);
  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\nhead: %p\n",
         slist_size(&l), slist_empty(&l), slist_front(&l), slist_back(&l),
         l.head);

  slist_destroy(&l);
  printf("\nlist destroyed\n");
  printf("size: %ld\nempty: %d\nfront: %d\nback: %d\nhead: %p\n",
         slist_size(&l), slist_empty(&l), slist_front(&l), slist_back(&l),
         l.head);
}


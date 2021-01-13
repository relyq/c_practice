#include <stdio.h>

#include "slist.h"

void slist_print(slist* l);

int main(void) {
  slist l = slist_create();
  for (int i = 7; i > -1; i--) {
    slist_pushfront(&l, i);
  }

  slist_pushback(&l, 0xff);

  slist_print(&l);

  printf("size: %d\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));

  printf("popfront = %d\n", slist_popfront(&l));
  printf("popback = %d\n", slist_popback(&l));

  slist_print(&l);
  printf("size: %d\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));

  slist_destroy(&l);
  printf("\nsize: %d\nempty: %d\nfront: %d\nback: %d\n", slist_size(&l),
         slist_empty(&l), slist_front(&l), slist_back(&l));
  return 0;
}

void slist_print(slist* l) {
  for (int i = 0; i < l->size; i++) {
    printf("%d\t", slist_at(l, i));
    if (!(i % 4)) printf("\n");
  }
  printf("\n\n");
}
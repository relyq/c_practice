#include <stdio.h>

#include "queue.h"

void slist_dump(slist* l);

int main() {
  queue q;
  q = queue_create();
  for (int i = 0; i < 5; i++) queue_push(&q, i);

  slist_dump(q.list);

  printf("front: %d\nback: %d\n", queue_front(&q), queue_back(&q));
  printf("\n");

  for (int i = 0; i < 5; i++) printf("popped: %d\n", queue_pop(&q));

  printf("\n");
  queue_destroy(&q);
  printf("q.size: %ld\nq.list: %p\n", q.size, q.list);
  return 0;
}

void slist_dump(slist* l) {
  printf("&l: %p\tl.head: %p\tl.tail: %p\tl.size: %ld\n", &l, l->head, l->tail,
         l->size);
  for (size_t i = 0; i < l->size; i++) {
    int item = slist_at(l, i);
    sl_node* node = slist_goto(l->head, i);
    printf("l[%ld].item: %d\t&l[%ld]: %p\tl[%ld].next: %p\n", i, item, i, node,
           i, node->next);
  }
  printf("\n");
}

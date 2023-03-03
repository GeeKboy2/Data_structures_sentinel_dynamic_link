#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "link.h"

void print_link(struct link *l) {
  struct lelement *head = lnk__first(l);
  while (!llm__is_end_mark(head)) {
    printf("%d,", head->data);
    head = llm__next(head);
  }
  printf("\n");
}

void testing() {
  struct lelement sentinel = {0, (struct lelement *)&sentinel};
  struct link link = lnk__empty();
  struct lelement head = {.data = 1, .next = NULL};
  struct lelement element = {.data = 5, .next = NULL};
  struct lelement third = {.data = 3, .next = NULL};

  printf("sentinel is %d\n", llm__is_end_mark(&sentinel));

  print_link(&link);

  lnk__add_head(&link, &head);

  print_link(&link);

  lnk__add_after(&link, &head, &element);

  print_link(&link);

  lnk__add_after(&link, &head, &third);

  print_link(&link);

  printf("test du head %p == %p\n", lnk__first(&link), &head);
  printf("test du next %p == %p\n", llm__next(&head), &third);

  lnk__remove_after(&link, &head);

  print_link(&link);

  lnk__remove_after(&link, &head);

  print_link(&link);

  lnk__remove_head(&link);

  print_link(&link);
}

int main() {
  printf("%s\n", __FILE__);

  testing();

  return EXIT_SUCCESS;
}
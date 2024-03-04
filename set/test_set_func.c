#include "set.h"
#include <assert.h>
#include <stdio.h>

static void test_create_set(void) {
  printf("%s", __func__);
  struct set *st = set__empty();

  assert(set__is_empty(st));
  assert(set__size(st) == 0);
  assert(!set__find(st, 11));

  assert(set__remove(st, 78) != 0);

  set__free(st);

  printf("\tOK create_set\n");
}

int is_even(int x) { return x % 2 == 0; }

void test_filter(void) {
  struct set *st = set__empty();

  set__add(st, 1);
  set__add(st, 2);
  set__add(st, 3);
  set__add(st, 4);
  set__add(st, 5);
  set__add(st, 6);


  set__print(st);

  struct set *se = set__filter(is_even, st);
  set__print(se);
  set__free(st);
  set__free(se);
  printf("\tOK filter_set\n");
}

int main(void) {
  printf("%s\n", __FILE__);

  test_create_set();
  test_filter();
  return 0;
}
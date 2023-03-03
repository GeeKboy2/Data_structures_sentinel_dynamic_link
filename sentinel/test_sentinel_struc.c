#include <assert.h>
#include <stdio.h>

#include "set_sentinel.h"

static void test_set__remove_with_shift (void) {
  printf("%s", __func__);

  
  struct set *st = set__empty();

  set__add(st,1);
  assert(st->s[0] == 1);
  set__add(st,2);
  assert(st->s[1] == 2);
  set__add(st,3);
  assert(st->s[2] == 3);
  set__add(st,4);
  assert(st->s[3] == 4);
  assert(st->s[4] == SET__BOUND);

  set__print(st);

  set__remove(st, 3);
  assert(st->s[0] == 1);
  assert(st->s[1] == 2);
  assert(st->s[2] == 4);
  assert(st->s[3] == SET__BOUND);

  set__remove(st, 4);
  assert(st->s[0] == 1);
  assert(st->s[1] == 2);
  assert(st->s[2] == SET__BOUND);

  set__remove(st, 1);
  assert(st->s[0] == 2);
  assert(st->s[1] == SET__BOUND);

  set__remove(st, 2);
  assert(st->s[0] == SET__BOUND);
  
  set__free(st);
  printf("\tOK remove\n");
}

static void test_set__add_with_shift (void){
  struct set *sl = set__empty();

  set__add(sl,1);
  assert(sl->s[0] == 1);
  set__add(sl,2);
  assert(sl->s[1] == 2);
  set__add(sl,3);
  assert(sl->s[2] == 3);
  set__add(sl,4);
  assert(sl->s[3] == 4);
  assert(sl->s[4] == SET__BOUND);


  set__print(sl);
  printf("taille %zu\n",set__size(sl));
  shift_right(sl->s,0);
  set__print(sl);

  printf("adding 30\n");
  set__add(sl, 30);
  set__print(sl);

  printf("adding 4\n");
  set__add(sl, 4);
  set__print(sl);

  printf("adding -11\n");
  set__add(sl, -11);
  set__print(sl);

  printf("adding 10\n");
  set__add(sl, 10);
  set__print(sl);

  set__free(sl);

  printf("\tOK add\n");
}

int main () {
  printf("%s\n", __FILE__);
  
  test_set__remove_with_shift();
  test_set__add_with_shift();
  return 0;
}
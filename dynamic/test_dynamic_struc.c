#include <stdio.h>
#include "set_dynamic.h"
#include <assert.h>

void free_after_empty(void){
  struct set *st=set__empty();

  set__free(st);
  printf("\tOK free_empty\n");
}

static void test_set__remove_with_shift (void) {
  printf("%s", __func__);

  struct set *st=set__empty();
  st->size=0;
  st->capacity=0;
  set__add(st,1);
  set__add(st,2);
  set__add(st,3);
  set__add(st,4);

  set__remove(st, 3);
  assert(st->s[0] == 1);
  assert(st->s[1] == 2);
  assert(st->s[2] == 4);
  

  set__remove(st, 4);
  assert(st->s[0] == 1);
  assert(st->s[1] == 2);


  set__remove(st, 1);
  assert(st->s[0] == 2);


  set__remove(st, 2);

  
  set__free(st);
  printf("\tOK remove\n");
}

static void test_set__add_with_shift (void){
  struct set *sl=set__empty();
  sl->size=0;
  sl->capacity=0;
  set__add(sl,1);
  set__add(sl,2);
  set__add(sl,3);
  set__add(sl,4);


  set__print(sl);
  shift_right(sl->s,sl->size,0);
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

int main (){
  printf("%s\n", __FILE__);

  free_after_empty();
  test_set__remove_with_shift();
  test_set__add_with_shift();   
  return 0;
}
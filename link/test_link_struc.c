#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "link.h"
#include "set_link.h"



void test_empty() {
  struct set *se = set__empty();
  set__free(se);
  printf("\tOK empty\n");
}

void test_find() {
  struct set *se = set__empty();
  
  set__add(se, 1);
  set__add(se, 2);
  set__add(se, 4);
  set__add(se, 5);
  set__add(se, 20);
  
  printf("found so %d\n",set__find(se,4));
  printf("not found so %d\n",set__find(se,6));


  struct lelement *head = lnk__first(se->l);
  while (!llm__is_end_mark(head)) {
    printf("%p,", head);
    head = llm__next(head);
  }
  printf("\n");

  printf("found (3) so %p\n", find(se->l, 4));
  printf("not found insert in (2-3) %p\n", find(se->l, 3));
  printf("not found insert in (0-1) %p\n", find(se->l, 0));

  
  set__free(se);

  printf("\tOK find\n");
}

void test_add() {

  struct set *se = set__empty();

  set__print(se);
  printf("is empty %d, taille %ld\n", set__is_empty(se), set__size(se));

  
  printf("added 2\n");
  set__add(se, 2);
  printf("taille %ld\n", set__size(se));
  set__print(se);
  
  printf("added 3\n");
  set__add(se, 3);
  printf("taille %ld\n", set__size(se));
  set__print(se);

  printf("added 0\n");
  set__add(se, 0);
  printf("taille %ld\n", set__size(se));
  set__print(se);

  printf("added 4\n");
  set__add(se, 4);
  printf("taille %ld\n", set__size(se));
  set__print(se);
  

  set__free(se);

  printf("\tOK add\n");
}

void test_remove(){
  struct set *se = set__empty();
  
  set__add(se, 1);
  set__add(se, 2);
  set__add(se, 4);
  set__add(se, 5);
  set__add(se, 20);
  set__print(se);

  printf("removed 4\n");
  set__remove(se,4);
  set__print(se);

  printf("removed 1\n");
  set__remove(se,1);
  set__print(se);


  printf("removed 20\n");
  set__remove(se,20);
  set__print(se);
  set__free(se);
  printf("\tOK remove\n");
}

int main() {
  printf("%s\n", __FILE__);

  test_empty();
  test_find();
  test_add();
  test_remove();

  return EXIT_SUCCESS;
}
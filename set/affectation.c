#include <stdio.h>

#include "set.h"

#if defined SENTINEL
#include "set_sentinel.h"
#elif defined DYNAMIC
#include "set_dynamic.h"
#elif defined LINK
#include "set_link.h"
#else
#error "A set implementation has to be defined"
#endif

int main () {
  printf("creation de s1 avec 5 elements\n");
  struct set *s1 = set__empty();

  set__add(s1, 111);
  set__add(s1, 222);
  set__add(s1, 333);
  set__add(s1, 444);
  set__add(s1, 555);

  struct set *s2 = set__empty();

  printf("affectation : s2 = s1\n");
  s2 = s1;
  printf("s2 nb element:resultat (5) -> %zu\n", set__size(s2));
 
  printf("\najouter 9 dans s1\n");
  set__add(s1, 9);

  printf("9 dans s2:resultat (NON) -> %s\n", set__find(s2, 9)? "OUI" : "NON");
  printf("s2 nb elements:resultat (5) -> %zu\n", set__size(s2));

  set__free(s1);
  set__free(s2);
  return 0;
}
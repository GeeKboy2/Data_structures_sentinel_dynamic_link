#include "set_sentinel.h"
#include <stdio.h>
#include <stdlib.h>

int set__find(const struct set *se, int c) {
  return se->s[find(se->s, c)] == c;
}

int set__remove(struct set *se, int c) {
  if (set__find(se, c) == 0) {
    return SET__BOUND;
  }
  if (se->s[0] == SET__BOUND) {
    return SET__BOUND;
  }
  shift_left(se->s, find(se->s, c));
  return 0;
}

size_t find(int const s[], int c) {
  int i = 0;
  while (s[i] != SET__BOUND) {
    if (s[i] >= c) {
      return i;
    }
    i++;
  }
  return i;
}

int len(int s[]) {
  int i = 0;
  while (s[i] != SET__BOUND) {
    i++;
  }
  return i;
}

void shift_right(int s[], size_t begin) {
  int i = len(s);
  while (i >= (int)begin) {
    s[i + 1] = s[i];
    i--;
  }
}

void shift_left(int s[], size_t begin) {
  size_t i = begin + 1;
  while (s[i - 1] != SET__BOUND) {
    s[i - 1] = s[i];
    i++;
  }
}

struct set *set__empty(void) {
  struct set *set=malloc(sizeof(struct set)) ;
  set->s[0] = SET__BOUND;
  return set;
}

int set__is_empty(const struct set *se) { return se->s[0] == SET__BOUND; }

size_t set__size(const struct set *se) {
  size_t i = 0;
  while (se->s[i] > SET__BOUND) {
    i++;
  }
  return i;
}

int set__add(struct set *se, int c) {
  if (c < 0) {
    return SET__BOUND;
  }
  if (set__size(se) >= SET__SIZE - 1) {
    return SET__BOUND;
  }
  if (set__find(se, c)) {
    return SET__BOUND;
  }
  size_t pos = find(se->s, c);
  shift_right(se->s, pos);
  se->s[pos] = c;
  return 0;
}

void set__print(const struct set *se) {
  printf("\n");
  for (size_t i = 0; i < set__size(se) + 1; i++) {
    printf("%d,", se->s[i]);
  }
  printf("\n");
}

void set__free(struct set *se) {
  free(se);
  //(void) se;
}




struct set * set__filter(int(*selection)(int),const struct set *s){
  struct set* st=set__empty();

  int i=0;
  while (s->s[i]!=-1) {
    if(selection(s->s[i])){
      set__add(st,s->s[i]);
    }
    i++;
  }
  return st;
}
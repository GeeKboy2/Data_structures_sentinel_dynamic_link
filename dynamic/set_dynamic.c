
#include "set_dynamic.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct set;

size_t find_recursive(int const s[], size_t start, size_t end, int c) {
  if (start == end) {
    return start;
  }

  size_t m = (start + end) / 2;
  if (s[m] >= c)
    return find_recursive(s, start, m, c);
  else
    return find_recursive(s, m + 1, end, c);
}

size_t find(int const s[], size_t size, int c) {
  return find_recursive(s, 0, size, c);
}
/*
size_t find(int const s[], size_t size, int c){
    for(size_t p = 0; p<size; p++){
        if(s[p] >= c ){
            return p;
        }
    }
    return size;
}
*/

void shift_right(int s[], size_t begin, size_t size) {
  for (size_t p = size; p > begin; p--) {
    s[p] = s[p - 1];
  }
}

void shift_left(int s[], size_t begin, size_t size) {
  for (size_t p = begin; p < size - 1; p++) {
    s[p] = s[p + 1];
  }
}

struct set *set__empty(void) {
  struct set *set = malloc(sizeof(struct set));
  // est-ce qu'il faut alloc ici ou dans le add quand on ajoute
  set->size = 0;
  set->capacity = 0;
  set->s = NULL;
  return set;
}

int set__is_empty(const struct set *se) { return se->size == 0; }

int set__find(const struct set *se, int c) {
  if (se->size == 0) {
    return 0;
  }
  size_t p = find(se->s, se->size, c);
  return se->s[p] == c;
}

size_t set__size(const struct set *se) { return se->size; }

int set__add(struct set *se, int c) {
  if (c < 0) {
    return -1;
  }

  if (se->size == 0) {
    se->capacity++;
    se->s = (int *)malloc(se->capacity * sizeof(int));
    se->s[se->size] = c;
    se->size++;
    return 0;
  }

  size_t p = find(se->s, se->size, c);
  if (p == se->size) {
    if (se->s[p - 1] == c) {
      return -1;
    }
  } else if (se->s[p] == c) {
    return -1;
  }

  if (se->size == se->capacity) {
    se->capacity *= 2;
  }

  se->s = (int *)realloc(se->s, se->capacity * sizeof(int));
  shift_right(se->s, p, se->size);
  se->s[p] = c;
  se->size++;
  return 0;
}

int set__remove(struct set *se, int c) {
  size_t p = find(se->s, se->size, c);
  if (se->size == 0 || c < 0 || find(se->s, se->size, 0) == se->size ||
      se->s[p] != c) {
    return -1;
  }

  shift_left(se->s, p, se->size);
  se->size--;

  if (se->size > se->capacity / 2) {
    return 0;
  }

  if (se->capacity == 1) {
    se->capacity = 0;
    free(se->s);
    return 0;
  }

  se->capacity /= 2;
  se->s = (int *)realloc(se->s, se->capacity * sizeof(int));
  return 0;
}

void set__print(const struct set *se) {
  size_t i = 0;
  printf(".size = %ld, .capacity = %ld, .s = ", se->size, se->capacity);
  while (se->size > i && se->s != NULL) {
    printf(" %d", se->s[i]);
    i++;
  }
  printf(" \n");
}

void set__free(struct set *se) {
  if (se->size > 0) {
    free(se->s);
  }

  se->s = NULL;
  se->capacity = 0;
  se->size = 0;
  free(se);
}

struct set *set__filter(int(*selection)(int),const struct set *s) {
  struct set *st = set__empty();

  size_t i = 0;
  while (i < s->size) {
    if (selection(s->s[i])) {
      set__add(st, s->s[i]);
    }
    i++;
  }
  return st;
}

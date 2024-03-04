#include "set_link.h"
#include "link.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Find a struct lelement after which f can be inserted, or returns
// the head if the element must be inserted in head.
// pre-condition:  l sort by increasing order.
struct lelement *find(struct link *l, int f) {
  struct lelement *head = lnk__first(l);
  struct lelement *before;
  while (!llm__is_end_mark(head)) {
    before = head;
    head = head->next;
    if (head->data >= f) {
      return before;
    }
  }
  return lnk__first(l);
}

// Return a struct set representing the empty set
struct set *set__empty(void) {
  /*
  this old version with the first test in test_link_struct doesn't work and i still don't know why.
  struct set *se=malloc(sizeof(struct set *));
  struct link *link = malloc(sizeof(struct link *));
  *link = lnk__empty();
  se->l = link;
  */
  struct set *se = malloc(sizeof(struct set));
  struct link* lnk=malloc(sizeof(struct link));
  *lnk= lnk__empty();
  se->l=lnk;
  
  
  return se;
}

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set *se) { return se->l->head == SENTINEL; }

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c) {
  struct lelement *head = se->l->head;
  while (!llm__is_end_mark(head)) {
    if (head->data == c) {
      return 1;
    }
    head = head->next;
  }
  return 0;
}

// Returns the number of elements in se
size_t set__size(const struct set *se) {
  size_t i = 0;
  struct lelement *head = se->l->head;
  while (!llm__is_end_mark(head)) {
    head = head->next;
    i++;
  }
  return i;
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c) {
  if (c < 0) {
    printf("négative");
    return -1;
  }
  
  if (set__find(se, c)) {
    return -1;
  }
  
  
  //Why does this fomulation not work and tell me invalid write or read size 8 at the line 81
  //struct lelement *add=malloc(sizeof(struct lelement *));
  struct lelement *add = (struct lelement *) malloc(sizeof(struct lelement));

  //printf("adress for add alloced %p",add);
  add->data = c;
  add->next = NULL;

  if (set__is_empty(se)) {
    //printf("adding to empty");
    lnk__add_head(se->l, add);
    return 0;
  }
  struct lelement *head = find(se->l, c);

  if (head->data > c) {
    //printf("adding to head");
    lnk__add_head(se->l, add);
  } else {
    //printf("adding after %d", head->data);
    lnk__add_after(se->l, head, add);
  }
  return 0;
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
/*
int set__remove(struct set *se, int c) {
  if (!set__find(se, c)) {
    return -1;
  }
  struct lelement *target = find(se->l, c);
  //printf("target data %d\n",target->data);
  if (target->data > se->l->head->data) {
    free(lnk__remove_after(se->l, target));
  } else {
    printf("remove head\n");
    free(lnk__remove_head(se->l));
  }
  //free(target);
  return 0;
}
*/
int set__remove(struct set *se, int c){
    if(c<0 || set__find(se,c)==0 || llm__is_end_mark(se->l->head)) 
        return -1;
    struct lelement *after=find(se->l,c);
    if(se->l->head->data==c){
        struct lelement *tmp=lnk__remove_head(se->l);
        free(tmp);
        return 0;
    }   
    struct lelement *tmp=lnk__remove_after(se->l,after);
    tmp->data=0; /*-------------------*/
    free(tmp);
    return 0;
}

// helper function for debugging : display all elements in se
void set__print(const struct set *se) {
  struct lelement *head = lnk__first(se->l);
  while (!llm__is_end_mark(head)) {
    printf("%d,", head->data);
    head = llm__next(head);
  }
  printf("\n");
}

void set__free(struct set *se) {
  struct lelement *head = lnk__first(se->l);
  struct lelement *before;
  while (!llm__is_end_mark(head)) {
    before=head;
    head = head->next;
    free(before);
  }
  free(se->l);
  free(se);
}


struct set * set__filter(int(*selection)(int),const struct set *s){
  struct set* st=set__empty();
  struct lelement *head = lnk__first(s->l);
  while (!llm__is_end_mark(head)) {
    if(selection(head->data)){
      set__add(st,head->data);
    }
    head = llm__next(head);
  }
  return st;
}
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "link.h"

const struct lelement sentinel = {INT_MAX, (struct lelement *)&sentinel};

// Retourne un booléen attestant si `e` est la butée
int llm__is_end_mark(const struct lelement *e) { return e == SENTINEL; }

// Retourne le maillon suivant le maillon `e`
struct lelement *llm__next(const struct lelement *e) {
  return e->next;
}

// Crée une liste vide
// Post : le champ `head` pointe sur la butée
struct link lnk__empty(void) {
  struct link link = {.head = SENTINEL};
  return link;
}

// Retourne le 1er maillon de la liste `l`
struct lelement *lnk__first(const struct link *l) {
  return l->head;
}

// Ajoute le maillon `add` en tête de la liste `l`
// Pre : add->next == NULL,
//       add n'est pas la butée
int lnk__add_head(struct link *l, struct lelement *add) {
  struct lelement *first = lnk__first(l);
  add->next = first;
  l->head = add;
  return 1;
}

// Enlève le premier maillon de la liste `l` et le retourne
// Si la liste est vide, renvoie NULL.
// Post : return->next == NULL || return == NULL
struct lelement *lnk__remove_head(struct link *l) {
  struct lelement *first = lnk__first(l);
  if (llm__is_end_mark(first)) {
    return NULL;
  }
  l->head=first->next;
  first->next=NULL;
  return first;
}

// Ajoute le maillon `add` à la suite du maillon `after` dans
// la liste `l`
// Rq : `l` peut ne pas être utilisé dans cette fonction.
// Pre : after n'est pas la butée,
//       add n'est pas la butée,
//       after->next != NULL,
//       add->next == NULL
int lnk__add_after(struct link *l, struct lelement *after,
                   struct lelement *add) {
  add->next = after->next;
  after->next = add;
  (void)l;
  return 1;
}

// Enlève le maillon se trouvant *après* `after` dans la liste `l` et
// le retourne. Renvoie NULL si le maillon après `after` est la butée.
// Pre  : after n'est pas la butée
//        after->next != NULL
// Post : return->next == NULL || return == NULL
struct lelement *lnk__remove_after(struct link *l, struct lelement *after) {
  (void)l;
  if (llm__is_end_mark(after->next) || llm__is_end_mark(after)) {
    return NULL;
  }
  struct lelement * r=after->next;
  after->next = after->next->next;
  r->next=NULL;
  return r;
}


#ifndef __SET_LINK__
#define __SET_LINK__

#include "set.h"

struct link;

struct set {
  struct link *l;
};

// Find a struct lelement after which f can be inserted, or returns
// the head if the element must be inserted in head.
// pre-condition:  l sort by increasing order.
struct lelement * find(struct link *l, int f);


#endif /* __SET_LINK__ */
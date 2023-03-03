#ifndef __SET_SENTINEL_H__
#define __SET_SENTINEL_H__

#include<stddef.h>

#ifndef SET__SIZE
#define SET__SIZE 10
#endif

#define SET__BOUND (-1)  // sentinel

struct set {
  int s[SET__SIZE];
};

#include "set.h"

// returns the first position p in s such that s[p]>=c if any, or
// the position of SET__BOUND otherwise.
size_t find(int const s[], int c);

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the right.
// The value in s[begin] is left unchanged.
void shift_right(int s[], size_t begin);

// moves all elements in s starting from position begin and up to
// SET__BOUND included, one position to the left. 
void shift_left(int s[], size_t begin);

#endif //__SET_SENTINEL_H__

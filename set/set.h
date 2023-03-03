#ifndef __SET_H__
#define __SET_H__

#include <stddef.h>

struct set;

// Return a struct set representing the empty set
struct set *set__empty(void);

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c);

// Returns the number of elements in se
size_t set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c);

//helper function for debugging : display all elements in se
void set__print(const struct set* se);

void set__free(struct set * se);

struct set * set__filter(int(*selection)(int),const struct set *s);
#endif // __SET_H__

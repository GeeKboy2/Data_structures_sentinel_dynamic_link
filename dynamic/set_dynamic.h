#ifndef __SET_DYNAMIC_H__
#define __SET_DYNAMIC_H__

#include <stddef.h>

#include "set.h"

struct set{
    int * s;
    size_t capacity;
    size_t size;
};



size_t find(const int *s,size_t size ,int c);

void shift_left(int *s,size_t size ,size_t begin);

void shift_right(int *s,size_t size,size_t begin);


#endif //__SET_DYNAMIC_H__
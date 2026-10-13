#ifndef Setarray
#define Setarray

#include<stddef.h>

typedef struct{
    char **data;
    int length;
    int capacity;
}strset;

void strset_init(strset *set);

int strset_size(const strset *set);

#endif

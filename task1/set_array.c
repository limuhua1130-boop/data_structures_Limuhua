#include"set_array.h"

void strset_init(strset *set){
    set->data=NULL;
    set->length=0;
    set->capacity=0;
}

int strset_size(const strset *set){
    return set->length;
}

#include<stdio.h>
#include"set_array.h"

int main(){
    strset set;
    strset_init(&set);

    printf("length: %d\n",strset_size(&set));
    return 0;
}

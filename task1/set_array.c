#include"set_array.h"
#include<string.h>

void strset_init(strArrset *set){
    //set->data=NULL;
    set->length=0;
    //set->capacity=0;
}

int strset_size(const strArrset *set){
    return set->length;
}

int strset_exist(const strArrset *set,const char *value){
    for(int i=0;i<set->length;i++){
        if(!strcmp(set->data[i],value)){
            return i;
        }
    }
    return -1;
}

int strset_add(strArrset *set,const char *val){
    if(strset_exist(set,val)!=-1){
        return 0;
    }
    if(set->length>=CAPACITY){
        return -1;
    }
    if(strlen(val)>=MAX_TEXT_SIZE){
        return -2;
    }
    strcpy(set->data[set->length++],val);
    return 1;
}

int strset_remove(strArrset *set,const char *val){
    for(int i=0;i<set->length;i++){
        if(strcmp(set->data[i],val)==0){
            if(i!=set->length-1){
                strcpy(set->data[i],set->data[set->length-1]);//无需有序，减少复杂度
            }
            set->length--;
            return 1;
        }
    }
    return 0;
}

void strset_clear(strArrset *set){
    set->length=0;
    return;
}
#ifndef Setarray
#define Setarray

#include<stddef.h>

#define CAPACITY 100
#define MAX_TEXT_SIZE 100

typedef struct{
    char data[CAPACITY][MAX_TEXT_SIZE];
    int length;
    //int capacity;
}strArrset;

void strset_init(strArrset *set);

int strset_size(const strArrset *set);

int strset_exist(const strArrset *set,const char *val);

int strset_add(strArrset *set,const char *val);

int strset_remove(strArrset *set,const char *val);

void strset_clear(strArrset *set);

int strset_subset(const strArrset *a,const strArrset *b);

int strset_union(const strArrset *a,const strArrset *b,strArrset *res);

int strset_intersection(const strArrset *a,const strArrset *b,strArrset *res);

int strset_diff(const strArrset *a,const strArrset *b,strArrset *res);

#endif

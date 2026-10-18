#ifndef Setlinklist
#define Setlinklist

#include<stddef.h>

#define MAX_TEXT_SIZE 100

typedef struct strNode{
    char data[MAX_TEXT_SIZE];
    struct strNode *next;
}strNode;

typedef struct{
    strNode *head;
    int length;
}strListset;

void strlist_init(strListset *set);
void strlist_clear(strListset *set);
int strlist_size(const strListset *set);
int strlist_exist(const strListset *set,const char *val);
int strlist_add(strListset *set,const char *val);
int strlist_remove(strListset *set,const char *val);

int strlist_subset(const strListset *a,const strListset *b);
int strlist_union(const strListset *a,const strListset *b,strListset *res);
int strlist_intersection(const strListset *a,const strListset *b,strListset *res);
int strlist_diff(const strListset *a,const strListset *b,strListset *res);

#endif
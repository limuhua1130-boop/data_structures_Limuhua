#include<string.h>
#include<stdlib.h>

#include "set_linklist.h"

void strlist_init(strListset *set){
    set->head=NULL;
    set->length=0;
    return;
}

void strlist_clear(strListset *set){
    strNode *cur=set->head;
    while(cur!=NULL){
        strNode *next=cur->next;
        free(cur);
        cur=next;
    }
    set->head=NULL;
    set->length=0;
    return;
}

int strlist_size(const strListset *set){
    return set->length;
}

int strlist_exist(const strListset *set,const char *val){
    const strNode *cur=set->head;
    int idx=0;
    while(cur!=NULL){
        if(strcmp(cur->data,val)==0){
            return idx;
        }
        cur=cur->next;
        idx++;
    }
    return -1;
}

int strlist_add(strListset *set,const char *val){
    if(strlist_exist(set,val)!=-1){
        return 1;
    }
    if(strlen(val)>=MAX_TEXT_SIZE){
        return -2;
    }

    strNode *tep=malloc(sizeof *tep);
    strcpy(tep->data,val);
    tep->next=set->head;
    set->head=tep;
    set->length++;
    return 0;
}

int strlist_remove(strListset *set,const char *val){

    if(set->length==0){
        return 0;
    }

    strNode *cur=set->head;
    if(strcmp(cur->data,val)==0){
        set->head=set->head->next;
        set->length--;
        free(cur);
        return 1;
    }
    strNode *pre=cur;
    cur=cur->next;
    while(cur!=NULL){
        if(strcmp(cur->data,val)==0){
            pre->next=cur->next;
            free(cur);
            set->length--;
            return 1;
        }
        pre=cur;
        cur=cur->next;
    }
    return 0;
}


int strlist_subset(const strListset *a,const strListset *b){
    strNode *cur=a->head;
    while(cur!=NULL){
        if(strlist_exist(b,cur->data)==-1){
            return 0;
        }
        cur=cur->next;
    }
    return 1;
}

int strlist_union(const strListset *a,const strListset *b,strListset *res){
    strlist_clear(res);

    for(strNode *cur=a->head;cur!=NULL;cur=cur->next){
        int result=strlist_add(res,cur->data);
        if(result<0){
            strlist_clear(res);
            return result;
        }
    }
    for(strNode *cur=b->head;cur!=NULL;cur=cur->next){
        int result=strlist_add(res,cur->data);
        if(result<0){
            strlist_clear(res);
            return result;
        }
    }

    return 0;
}

int strlist_intersection(const strListset *a,const strListset *b,strListset *res){
    strlist_clear(res);

    for(strNode *cur=a->head;cur!=NULL;cur=cur->next){
        if(strlist_exist(b,cur->data)!=-1){
            int result=strlist_add(res,cur->data);
            if(result<0){
                strlist_clear(res);
                return result;
            }
        }
    }

    return 0;
}

int strlist_diff(const strListset *a,const strListset *b,strListset *res){
    strlist_clear(res);

    for(strNode *cur=a->head;cur!=NULL;cur=cur->next){
        if(strlist_exist(b,cur->data)==-1){
            int result=strlist_add(res,cur->data);
            if(result<0){
                strlist_clear(res);
                return result;
            }
        }
    }

    return 0;
}

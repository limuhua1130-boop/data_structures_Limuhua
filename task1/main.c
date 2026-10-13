#include<stdio.h>
#include"set_array.h"

void display(const strArrset *set){
    for(int i=0;i<set->length;i++){
        printf("%s\n",set->data[i]);
    }
    printf("\n");
}

void demo(){
    strArrset set;
    strset_init(&set);//测试初始化
    strset_add(&set,"test1");//测试添加
    int x=strset_add(&set,"test1");
    printf("重复添加返回值%d，长度%d\n",x,set.length);
    char val[MAX_TEXT_SIZE];
    for(int i=0;i<CAPACITY;i++){
        snprintf(val,sizeof val,"Test%d",i);//从AI处学习循环生成不同字符串
        x=strset_add(&set,val);
        if(x==-1){
            printf("len超限限制正常（若多次出现则不正常）\n");
        }
    }

    strset_clear(&set);
    printf("清空后长度为%d\n",set.length);


    char longstr[MAX_TEXT_SIZE+1];
    char norstr[MAX_TEXT_SIZE];
    for(int i=0;i<MAX_TEXT_SIZE;i++){
        longstr[i]='A';
        norstr[i]='A';
    }
    longstr[MAX_TEXT_SIZE]='\0';
    norstr[MAX_TEXT_SIZE-1]='\0';
    x=strset_add(&set,longstr);
    printf("超长字符串MAX+1返回值：%d，集合大小%d\n",x,set.length);
    x=strset_add(&set,norstr);
    printf("长字符串MAX返回值：%d，集合大小%d\n",x,set.length);
    
    
    strset_clear(&set);
    printf("清空后长度为%d\n",set.length);

    strset_add(&set,"test1");
    strset_add(&set,"test2");
    strset_add(&set,"test3");

    printf("寻找test1:%d\n",strset_exist(&set,"test1"));
    printf("寻找test4:%d\n",strset_exist(&set,"test4"));

    display(&set);
    x=strset_remove(&set,"test2");
    printf("remove返回值：%d\n",x);
    display(&set);
    x=strset_remove(&set,"test4");
    printf("remove返回值：%d\n",x);
    display(&set);

    return;
}

int main(){
    demo();
    return 0;
}

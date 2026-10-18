#include<stdio.h>
#include"set_array.h"
#include"set_linklist.h"

void display(const strArrset *set){
    for(int i=0;i<set->length;i++){
        printf("%s\n",set->data[i]);
    }
    printf("\n");
}

void display_list(const strListset *set){
    const strNode *cur=set->head;
    while(cur!=NULL){
        printf("%s\n",cur->data);
        cur=cur->next;
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

void test_set_operations(){
    strArrset a,b,empty,res;
    strset_init(&a);
    strset_init(&b);
    strset_init(&empty);

    strset_add(&a,"a");
    strset_add(&a,"b");
    strset_add(&b,"b");
    strset_add(&b,"c");

    printf("集合A：\n");
    display(&a);
    printf("集合B：\n");
    display(&b);

    printf("A是否为B的子集：%d（预期0）\n",strset_subset(&a,&b));
    printf("A是否为A的子集：%d（预期1）\n",strset_subset(&a,&a));
    printf("空集是否为A的子集：%d（预期1）\n",strset_subset(&empty,&a));

    int x=strset_union(&a,&b,&res);
    printf("并集返回值%d，长度%d（预期0，3）\n",x,strset_size(&res));
    if(x==0){
        display(&res);
    }

    x=strset_intersection(&a,&b,&res);
    printf("交集返回值%d，长度%d（预期0，1）\n",x,strset_size(&res));
    if(x==0){
        display(&res);
    }

    x=strset_union(&a,&empty,&res);
    printf("A与空集的并集：返回值%d，长度%d（预期0，2）\n",
           x,strset_size(&res));

    x=strset_intersection(&a,&empty,&res);
    printf("A与空集的交集：返回值%d，长度%d（预期0，0）\n",
           x,strset_size(&res));

    x=strset_diff(&a,&b,&res);
    printf("A-B返回值%d，长度%d（预期0，1）\n",x,strset_size(&res));
    if(x==0){
        printf("A-B是否包含a：%d（预期1）\n",strset_exist(&res,"a")!=-1);
        display(&res);
    }

    x=strset_diff(&b,&a,&res);
    printf("B-A返回值%d，长度%d（预期0，1）\n",x,strset_size(&res));
    if(x==0){
        printf("B-A是否包含c：%d（预期1）\n",strset_exist(&res,"c")!=-1);
        display(&res);
    }

    x=strset_diff(&a,&a,&res);
    printf("A-A返回值%d，长度%d（预期0，0）\n",x,strset_size(&res));

    x=strset_diff(&a,&empty,&res);
    printf("A与空集的差集：返回值%d，长度%d（预期0，2）\n",
           x,strset_size(&res));
    if(x==0){
        display(&res);
    }

    x=strset_diff(&empty,&a,&res);
    printf("空集与A的差集：返回值%d，长度%d（预期0，0）\n",
           x,strset_size(&res));

    printf("运算后A长度%d，B长度%d（预期2，2）\n",
           strset_size(&a),strset_size(&b));
}

void demo_list(){
    strListset set,a,b,empty,res;
    strlist_init(&set);
    strlist_init(&a);
    strlist_init(&b);
    strlist_init(&empty);
    strlist_init(&res);

    printf("链表初始化长度%d（预期0）\n",strlist_size(&set));
    strlist_add(&set,"tail");
    int x=strlist_add(&set,"tail");
    printf("链表重复添加返回值%d，长度%d（预期1，1）\n",x,strlist_size(&set));
    strlist_add(&set,"middle");
    strlist_add(&set,"head");
    printf("链表寻找middle：%d，寻找missing：%d（预期1，0）\n",
           strlist_exist(&set,"middle")!=-1,strlist_exist(&set,"missing")!=-1);
    display_list(&set);

    x=strlist_remove(&set,"missing");
    printf("删除不存在节点返回值%d，长度%d（当前实现预期-1，3）\n",
           x,strlist_size(&set));

    x=strlist_remove(&set,"middle");
    printf("删除中间节点返回值%d，长度%d（当前实现预期0，2）\n",x,strlist_size(&set));
    x=strlist_remove(&set,"head");
    printf("删除头节点返回值%d，长度%d（当前实现预期0，1）\n",x,strlist_size(&set));
    x=strlist_remove(&set,"tail");
    printf("删除尾节点返回值%d，长度%d（当前实现预期0，0）\n",x,strlist_size(&set));

    char longstr[MAX_TEXT_SIZE+1];
    for(int i=0;i<MAX_TEXT_SIZE;i++){
        longstr[i]='A';
    }
    longstr[MAX_TEXT_SIZE]='\0';
    x=strlist_add(&set,longstr);
    printf("链表超长字符串返回值%d，长度%d（预期-2，0）\n",x,strlist_size(&set));

    strlist_add(&a,"a");
    strlist_add(&a,"b");
    strlist_add(&b,"b");
    strlist_add(&b,"c");

    printf("链表集合A：\n");
    display_list(&a);
    printf("链表集合B：\n");
    display_list(&b);
    printf("链表A是否为B的子集：%d（预期0）\n",strlist_subset(&a,&b));
    printf("链表A是否为A的子集：%d（预期1）\n",strlist_subset(&a,&a));
    printf("链表空集是否为A的子集：%d（预期1）\n",strlist_subset(&empty,&a));

    x=strlist_union(&a,&b,&res);
    printf("链表并集返回值%d，长度%d（预期0，3）\n",x,strlist_size(&res));
    if(x==0){
        display_list(&res);
    }

    x=strlist_intersection(&a,&b,&res);
    printf("链表交集返回值%d，长度%d（预期0，1）\n",x,strlist_size(&res));
    if(x==0){
        display_list(&res);
    }

    x=strlist_diff(&a,&b,&res);
    printf("链表A-B返回值%d，长度%d（预期0，1）\n",x,strlist_size(&res));
    if(x==0){
        display_list(&res);
    }
    x=strlist_diff(&b,&a,&res);
    printf("链表B-A返回值%d，长度%d（预期0，1）\n",x,strlist_size(&res));
    if(x==0){
        display_list(&res);
    }

    x=strlist_diff(&a,&a,&res);
    printf("链表A-A返回值%d，长度%d（预期0，0）\n",x,strlist_size(&res));
    x=strlist_union(&a,&empty,&res);
    printf("链表A与空集的并集：返回值%d，长度%d（预期0，2）\n",
           x,strlist_size(&res));
    x=strlist_intersection(&a,&empty,&res);
    printf("链表A与空集的交集：返回值%d，长度%d（预期0，0）\n",
           x,strlist_size(&res));
    printf("链表运算后A长度%d，B长度%d（预期2，2）\n",
           strlist_size(&a),strlist_size(&b));

    strlist_clear(&set);
    strlist_clear(&a);
    strlist_clear(&b);
    strlist_clear(&empty);
    strlist_clear(&res);
    printf("链表清空后长度%d（预期0）\n",strlist_size(&set));
}

int main(){
    demo();
    test_set_operations();
    demo_list();
    return 0;
}

#include<stdio.h>
#include<string.h>
#include"formatter.h"

void display(const State *state){
    printf("[%s]\n",state->cur);
    printf("\n");
}

void demo(){
    State state;
    int x=state_init(&state,Page_len);//测试初始化
    printf("初始化返回值%d，长度%d，页内行数%d，页码%d（预期0，0，0，1）\n",
           x,state.len,state.page_lines,state.pages);

    int first=1;
    x=is_cap(&state,"hello",first);
    printf("首词hello能否放入：%d（预期1）\n",x);

    x=add(&state,"hello",&first);//测试添加首词和缩进
    printf("添加首词返回值%d，长度%d，first为%d（预期0，%d，0）\n",
           x,state.len,first,Indent+5);
    display(&state);

    x=add(&state,"world",&first);//测试单词间添加一个空格
    printf("添加第二个单词返回值%d，长度%d（预期0，%d）\n",
           x,state.len,Indent+11);
    display(&state);

    printf("输出当前行：\n");
    x=output(&state);
    printf("输出返回值%d，长度%d，页内行数%d，页码%d（预期0，0，1，1）\n",
           x,state.len,state.page_lines,state.pages);

    x=output(&state);//测试空缓冲区不会多输出一行
    printf("重复输出空行返回值%d，页内行数%d（预期0，1）\n",
           x,state.page_lines);

    state_clear(&state);
    printf("释放后指针是否为空%d，长度%d，页内行数%d，页码%d（预期1，0，0，0）\n\n",
           state.cur==NULL,state.len,state.page_lines,state.pages);
}

void test_capacity(){
    State state;
    state_init(&state,Page_len);

    printf("空行放入普通单词：%d（预期1）\n",
           is_cap(&state,"hello",1));

    char word[Page_len+1];
    for(int i=0;i<Page_len;i++){
        word[i]='A';
    }
    word[Page_len]='\0';

    printf("非段首放入页宽长度的单词：%d（预期1）\n",
           is_cap(&state,word,0));
    printf("段首放入页宽长度的单词：%d（预期0，缩进占用空间）\n",
           is_cap(&state,word,1));

    word[Page_len-Indent]='\0';
    printf("首词加缩进恰好填满一行：%d（预期1）\n",
           is_cap(&state,word,1));

    word[Page_len-Indent]='A';
    word[Page_len-Indent+1]='\0';
    printf("首词加缩进超出一字符：%d（预期0）\n",
           is_cap(&state,word,1));

    int first=1;
    add(&state,"hello",&first);
    for(int i=0;i<Page_len;i++){
        word[i]='A';
    }

    int remaining=Page_len-state.len-1;//留一个单词间空格
    word[remaining]='\0';
    printf("已有单词，再添加后恰好填满一行：%d（预期1）\n",
           is_cap(&state,word,first));

    word[remaining]='A';
    word[remaining+1]='\0';
    printf("已有单词，再添加后超出一字符：%d（预期0）\n\n",
           is_cap(&state,word,first));

    state_clear(&state);
}

void test_line_operations(){
    State state;
    state_init(&state,Page_len);
    int first=1;

    char word[Page_len+1];
    for(int i=0;i<Page_len-Indent;i++){
        word[i]='A';
    }
    word[Page_len-Indent]='\0';

    add(&state,word,&first);
    printf("首词加缩进后长度%d，first为%d（预期%d，0）\n",
           state.len,first,Page_len);

    int x=is_cap(&state,"tail!",first);
    printf("满行继续放入tail!：%d（预期0）\n",x);
    if(x==0){
        output(&state);
    }

    add(&state,"tail!",&first);
    printf("自动换行后长度%d，是否没有缩进%d，first为%d（预期5，1，0）\n",
           state.len,strcmp(state.cur,"tail!")==0,first);

    add(&state,"word,",&first);
    printf("追加带标点单词后是否为tail! word,：%d（预期1）\n",
           strcmp(state.cur,"tail! word,")==0);
    output(&state);

    first=1;//模拟新段落开始
    add(&state,"next",&first);
    printf("新段首词长度%d，first为%d（预期%d，0）\n",
           state.len,first,Indent+4);
    output(&state);

    state_clear(&state);
    printf("\n");
}

void test_pages(){
    State state;
    state_init(&state,Page_len);
    int first=0;

    state.page_lines=Page_num-1;//模拟本页只剩最后一行
    add(&state,"last",&first);
    output(&state);
    printf("恰好满页后页码%d，页内行数%d（预期1，%d）\n",
           state.pages,state.page_lines,Page_num);

    output(&state);//空缓冲区不能产生新的页面
    printf("满页后输出空缓冲区：页码%d，页内行数%d（预期1，%d）\n",
           state.pages,state.page_lines,Page_num);

    add(&state,"next",&first);
    output(&state);
    printf("满页后再输出一行：页码%d，页内行数%d（预期2，1）\n",
           state.pages,state.page_lines);

    state_clear(&state);
    printf("\n");
}

void test_format(){
    printf("整体排版测试，可尝试输入下面的文本：\n");
    printf("Hello,    world!\nThis is a test.\n\n\nNext paragraph.\n");
    printf("预期排版结果（段首缩进%d个空格）：\n",Indent);
    for(int i=0;i<Indent;i++){
        putchar(' ');
    }
    printf("Hello, world! This is a test.\n\n");
    for(int i=0;i<Indent;i++){
        putchar(' ');
    }
    printf("Next paragraph.\n\n");

    printf("请输入测试文本，Windows终端按Ctrl+Z再回车结束：\n");
    printf("实际排版结果：\n");
    int x=func();
    printf("整体排版返回值%d（预期0）\n",x);
}

int main(){
    demo();
    test_capacity();
    test_line_operations();
    test_pages();
    test_format();
    return 0;
}

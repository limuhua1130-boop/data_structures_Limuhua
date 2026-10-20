#include "formatter.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int state_init(State *state,int page_width){
    state->cur=malloc(page_width+1);

    if(state->cur==NULL){
        return -1;
    }
    state->cur[0]='\0';
    state->len=0;
    state->page_lines=0;
    state->pages=1;

    return 0;
}

void state_clear(State *state){
    if(state==NULL){
        return;
    }

    free(state->cur);
    state->cur=NULL;
    state->len=0;
    state->page_lines=0;
    state->pages=0;

    return;
}

int read_next(char **word){
    
    int len=0;
    (*word)[0]='\0';

    while(1){
        int ch=getchar();
        if(ch==' '){
            return 1;
        }
        if(ch=='\n'){
            return 2;
        }
        if(ch==EOF){
            return 3;
        }
        (*word)[len++]=ch;
        (*word)[len]='\0';
    }
}

int is_cap(const State *state,const char *word,int first){
    int need=state->len+(int)strlen(word);
    if(state->len>0){
        need++;
    }
    else if(first){
        need+=Indent;
    }
    return need<=Page_len;
}

int output(State *state){
    if(state->len==0){
        return 0;
    }
    if(state->page_lines==Page_num){
        putchar('\f');//换页符，AI推荐
        state->page_lines=0;
        state->pages++;
    }
    printf("%s\n",state->cur);
    state->page_lines++;
    state->cur[0]='\0';
    state->len=0;
    return 0;
}

int add(State *state,const char *word,int *first){
    if(state->len>0){
        state->cur[state->len++]=' ';
    }
    else if(*first){
        memset(state->cur,' ',Indent);//AI推荐，替代for循环
        state->len=Indent;
    }
    strcpy(state->cur+state->len,word);
    state->len+=(int)strlen(word);
    *first=0;
    return 0;
}

static void write_direct(State *state,const char *text,int indent){
    if(state->page_lines==Page_num){
        putchar('\f');
        state->page_lines=0;
        state->pages++;
    }
    for(int i=0;i<indent;i++){
        putchar(' ');
    }
    printf("%s\n",text);
    state->page_lines++;
    return;
}

int func(){
    State state;
    state_init(&state,Page_len);
    char *word=malloc(Page_len+1);
    
    int first=1;
    int input_line_has_text=0;
    int in_para=0;
    int pending_blank=0;

    while(1){
        int code=read_next(&word);
        if(word[0]!='\0'){
            input_line_has_text=1;

            if(pending_blank){
                write_direct(&state,"",0);
                pending_blank=0;
            }

            if(!is_cap(&state,word,first)){
                output(&state);
            }

            if(is_cap(&state,word,first)){
                add(&state,word,&first);
            }
            else{
                write_direct(&state,word,first?Indent:0);
                first=0;
            }
            in_para=1;
        }
        if(code==2){
            if(!input_line_has_text&&in_para){
                output(&state);

                first=1;
                in_para=0;
                pending_blank=1;
            }
            input_line_has_text=0;
        }
        if(code==3){
            output(&state);
            break;
        }
    }
    free(word);
    state_clear(&state);
    return 0;
}
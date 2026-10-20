#ifndef FORMATTER_H
#define FORMATTER_H

#define Indent 4
#define Page_len 80
#define Page_num 30

#define WORD 0
#define BLANK 1
#define END 2
#define ERR -1

typedef struct{
    char *cur;
    int len;
    int page_lines;
    int pages;
}State;

int state_init(State *state,int page_width);

void state_clear(State *state);

int read_next(char **word);

int is_cap(const State *state,const char *word,int first);

int add(State *state,const char *word,int *first);

int output(State *state);

int func();

#endif

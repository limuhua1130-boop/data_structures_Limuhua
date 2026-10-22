#include<stdio.h>
#include<string.h>
#include"generate_data.h"

int prepare_data(){
    char filename[256]="input";
    int num=20;
    int seed=114514;

    /*
    scanf("%s %d %d",filename,&num,&seed);
    */
   strcat(filename,".txt");
    int result=generator(filename,num,seed);
    if(result==0){
        printf("OK");
        return 0;
    }
    else{
        printf("NOT OK");
        return 1;
    }
}

int main(){
    int x=prepare_data();
    if(x==1){
        return 0;
    }
    
    return 0;
}
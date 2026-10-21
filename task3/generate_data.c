#include<stdio.h>
#include<stdlib.h>
#include"generate_data.h"

int generator(const char *filename,int count,int seed){
    if(filename==NULL||count<=0||seed<0){
        fprintf(stderr,"ERROR");//AI推荐：返回异常的放法
        return -1;
    }

    FILE *fp=fopen(filename,"w");
    if(fp==NULL){
        return -1;
    }
    srand(seed);

    for(int i=0;i<count;i++){
        int val=rand()%1000;
        fprintf(fp,"%d ",val);
    }
    fclose(fp);
    return 0;
}

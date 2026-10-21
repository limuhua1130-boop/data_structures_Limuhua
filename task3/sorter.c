#include"sorter.h"

int read_block(FILE *fp,int data[],int capacity){
    if(fp==NULL||data==NULL||capacity<=0){
        return -1;
    }
    int count=0;
    while(count<capacity){
        int result=fscanf(fp,"%d",&data[count]);
        if(result==1){
            count++;
        }
        else if(result==EOF&&!ferror(fp)){//AI认为应该加入错误判断
            break;
        }
        else{
            return -1;
        }
    }
    return count;
}

void sort_block(int data[],int count){
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(data[i]>data[j]){
                int tep=data[i];
                data[i]=data[j];
                data[j]=tep;
            }
        }
    }
    return;
}
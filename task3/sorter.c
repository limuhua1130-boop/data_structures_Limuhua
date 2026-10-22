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

int write_run(const char *filename,const int data[],int count){
    FILE *out=fopen(filename,"a");
    if(out==NULL){
        return -1;
    }
    for(int i=0;i<count;i++){
        if(fprintf(out,"%d ",data[i])<0){//AI认为这里需要加入错误判断
            fclose(out);
            return -1;
        }
    }
    fprintf(out,"\n");
    if(fclose(out)==EOF){
        return -1;
    }
    return 0;
}
int debug_check_run(const char *input_filename,const char *output_filename){
    FILE *input=fopen(input_filename,"r");
    FILE *output=fopen(output_filename,"w");
    if(input==NULL||output==NULL){
        return -1;
    }
    fclose(output);
    int data[MEMORY_CAP];
    int count;
    while(1){
        count=read_block(input,data,MEMORY_CAP);
        if(count<=0){
            break;
        }
        sort_block(data,count);
        write_run(output_filename,data,count);
    }
    fclose(input);
    return 0;
}
/*
int make_runs(const char *input_filename,const char *output_filename){
    FILE *input=fopen(input_filename,"r");
    FILE *output=fopen(output_filename,"w");
    if(input==NULL||output==NULL){
        return -1;
    }
    int data[MEMORY_CAP];
    int count;
    int total=0;
    while(1){
        count=read_block(input,data,MEMORY_CAP);
        if(count<=0){
            break;
        }
        sort_block(data,count);
        if(write_run(output_filename,data,count)){

        }
    }
}
*/

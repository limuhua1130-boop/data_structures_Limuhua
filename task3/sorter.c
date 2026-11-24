#include"sorter.h"
#include<stdlib.h>

int Min(int x,int y){
    return x>y?y:x;
}

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
int merge_pass(const char *source_filename,const char *destination_filename,int total,int run_length){
    FILE *left=fopen(source_filename,"r");
    FILE *right=fopen(source_filename,"r");
    FILE *out=fopen(destination_filename,"w");
    int result=-1;
    int ignored;
    if(left==NULL||right==NULL||out==NULL){
        goto cleanup;
    }
    for(int i=0;i<run_length;i++){//ri->下一行
        if(fscanf(right,"%d",&ignored)!=1){
            goto cleanup;
        }
    }
    for(int start=0;start<total;start+=2*run_length){
        int le=run_length;
        int ri=run_length;
        int a,b;
        if(fscanf(left,"%d",&a)!=1||fscanf(right,"%d",&b)!=1){
            goto cleanup;
        }
        while(le>0&&ri>0){
            if(a<=b){
                fprintf(out,"%d ",a);
                le--;
                if(le>0&&fscanf(left,"%d",&a)!=1){//有就读，没有就不读，GPT-6的天才设计
                    goto cleanup;
                }
            }
            else{
                fprintf(out,"%d ",b);
                ri--;
                if(ri>0&&fscanf(right,"%d",&b)!=1){
                    goto cleanup;
                }
            }
        }
        while(le>0){
            fprintf(out,"%d ",a);
            le--;
            if(le>0&&fscanf(left,"%d",&a)!=1){
                goto cleanup;
            }
        }
        while(ri>0){
            fprintf(out,"%d ",b);
            ri--;
            if(ri>0&&fscanf(right,"%d",&b)!=1){
                goto cleanup;
            }
        }

        fputc('\n',out);//From GPT-6

        if(start+2*run_length<total){
            for(int i=0;i<run_length;i++){
                if(fscanf(left,"%d",&ignored)!=1||fscanf(right,"%d",&ignored)!=1){
                    goto cleanup;
                }
            }
        }
    }
    result=0;
cleanup: 
    if(left!=NULL){
        fclose(left);
    }
    if(right!=NULL){
        fclose(right);
    }
    if(out!=NULL){
        fclose(out);
    }
    return result;
}
*/
int merge_pass(const char *source_filename,const char *destination_filename,int total,int run_length){
    if(total<=0||run_length<=0){
        return -1;
    }

    FILE *left=fopen(source_filename,"r");
    FILE *right=fopen(source_filename,"r");
    FILE *out=fopen(destination_filename,"w");

    int result=-1;
    int ignored;
    if(left==NULL||right==NULL||out==NULL){
        goto cleanup;
    }
    int first_left=Min(total,run_length);
    for(int i=0;i<first_left;i++){//ri->下一行
        if(fscanf(right,"%d",&ignored)!=1){
            goto cleanup;
        }
    }

    int start=0;
    while(start<total){
        int left_count=total-start;
        left_count=Min(left_count,run_length);
        int right_count=total-start-left_count;
        right_count=Min(right_count,run_length);
        int le=left_count,ri=right_count;
        int a,b;
        if(fscanf(left,"%d",&a)!=1){
            goto cleanup;
        }
        if(ri>0&&fscanf(right,"%d",&b)!=1){
            goto cleanup;
        }
        while(le>0&&ri>0){
            if(a<=b){
                fprintf(out,"%d ",a);
                le--;
                if(le>0&&fscanf(left,"%d",&a)!=1){
                    goto cleanup;
                }
            }
            else{
                fprintf(out,"%d ",b);
                ri--;
                if(ri>0&&fscanf(right,"%d",&b)!=1){
                    goto cleanup;
                }
            }
        }
        while(le>0){
            fprintf(out,"%d ",a);
            le--;
            if(le>0&&fscanf(left,"%d",&a)!=1){
                goto cleanup;
            }
        }
        while(ri>0){
            fprintf(out,"%d ",b);
            ri--;
            if(ri>0&&fscanf(right,"%d",&b)!=1){
                goto cleanup;
            }
        }

        fputc('\n',out);
        start+=left_count+right_count;
        if(start<total){
            for(int i=0;i<right_count;i++){
                if(fscanf(left,"%d",&ignored)!=1){
                    goto cleanup;
                }
            }
            int next_left=total-start;
            next_left=Min(next_left,run_length);
            for(int i=0;i<next_left;i++){
                if(fscanf(right,"%d",&ignored)!=1){
                    goto cleanup;
                }
            }
        }
    }
    result=0;
cleanup: 
    if(left!=NULL){
        fclose(left);
    }
    if(right!=NULL){
        fclose(right);
    }
    if(out!=NULL){
        fclose(out);
    }
    return result;
}
/*
int make_runs(const char *input_filename,const char *output_filename){
    FILE *input=fopen(input_filename,"r");
    FILE *output=fopen(output_filename,"w");
    if(input==NULL||output==NULL){
        fclose(input);
        fclose(output);
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
        if(write_run(output_filename,data,count)!=0){
            fclose(input);
            return -1;
        }
    }
    fclose(input);
    return count==0?count:-1;
}
*/
int make_runs(const char *input_filename,const char *output_filename,int capacity){
    if(capacity<=0){
        return -1;
    }
    FILE *input=fopen(input_filename,"r");
    FILE *output=fopen(output_filename,"w");

    if(input==NULL||output==NULL){
        fclose(input);
        fclose(output);
        return -1;
    }

    fclose(output);
    //int data[MEMORY_CAP];
    int *data=malloc((size_t)capacity*sizeof(int));
    if(data==NULL){
        fclose(input);
        return -1;
    }
    int count;
    int result=0;
    while(1){
        count=read_block(input,data,capacity);
        if(count<=0){
            break;
        }
        //count=read_block(input,data,MEMORY_CAP);
        //if(count<=0){
        //    break;
        //}
        sort_block(data,count);
        if(write_run(output_filename,data,count)!=0){
            result=-1;
            break;
        }
    }
    free(data);
    fclose(input);
    if(count<0){
        return -1;
    }
    return result;
}
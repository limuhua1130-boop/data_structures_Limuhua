#ifndef SORTER_H
#define SORTER_H

#include<stdio.h>

#define MEMORY_CAP 5

int read_block(FILE *fp,int data[],int capacity);

void sort_block(int data[],int count);

int write_run(const char *filename,const int data[],int count);

int make_runs(const char *input_filename,const char *output_filename);


int debug_check_run(const char *input_filename,const char *output_filename);
#endif
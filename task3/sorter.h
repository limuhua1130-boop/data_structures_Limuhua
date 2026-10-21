#ifndef SORTER_H
#define SORTER_H

#include<stdio.h>

#define MEMORY_CAP 5

int read_block(FILE *fp,int data[],int capacity);

void sort_block(int data[],int count);

#endif
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _EX1_H
#define _EX1_H
#define OK 1
#define NOT_OK 0


typedef struct
{
    int number;
    char name[50];
    char address[100];
} estudante;


#endif
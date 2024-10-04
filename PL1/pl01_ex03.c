#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    fork();fork();fork();
    printf("SCOMP!\n");
    exit(0);
}
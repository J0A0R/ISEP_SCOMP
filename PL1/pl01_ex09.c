#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void){
    pid_t p;
    int i, j;

    for (i = 0; i < 10; i++){
        p = fork();
        if (p == 0){
            for (j = i*100+1; j < ((i+1)*100); j++){
                printf("Value: %d\n",j);
            }
            exit(0);
        }
    }
    exit(0);


}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void){
    int status;
    pid_t p;

        printf("I'm..\n");
        p = fork();
        if (p == 0)
        {
            printf("I'll never join you!\n");
            exit(0);
        }
        waitpid(p,&status,0); 
        printf("the..\n");
        p = fork();
        if (p == 0)
        {
            printf("I'll never join you!\n");
            exit(0);
        }
        waitpid(p,&status,0); 
        printf("father!\n");
        p = fork();
        if (p == 0)
        {
            printf("I'll never join you!\n");
            exit(0);
        }
        exit(0);
}
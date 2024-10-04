#include <stdio.h>
#include <unistd.h>	
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () 
{
    int i;
    int status;
    pid_t par[4];
    pid_t p;
    int count;

    count = 0;
    for (i = 0; i < 4; i++)
    {
        p = fork();
        if (p == 0) {
            exit(i+1);	
        }
        else if (p % 2 == 0){
            par[count] = p;
            count++;
        }
    }
    for (i = 0; i <count; i++){
            waitpid(par[i],&status,0);
    }
    printf ("This is the end.\n");
    exit(0);
} 

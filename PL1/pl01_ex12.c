#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn_childs(int n);

int main(void){
    int n;
    int index;
    n = 6;
    index = spawn_childs(n);
    printf("Index:%d\n",index);
    exit(0);
}

int spawn_childs(int n){
    pid_t p;
    int i;
    int index;
    for (i = 0; i< n; i++){
        p = fork();
        if (p == 0){
           index = i+1; 
           return(index);
        }    
    }
    sleep(1);
    return(0);
}
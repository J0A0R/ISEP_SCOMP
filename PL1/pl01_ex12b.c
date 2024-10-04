#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn_childs();

int main(void){
    int index;
    index = spawn_childs();
    printf("Index:%d\n",index);
    exit(0);
}

int spawn_childs(){
    pid_t p;
    int i;
    int index;
    for (i = 0; i< 6; i++){
        p = fork();
        if (p == 0){
           index = (i+1)*2; 
           return(index);
        }    
    }
    wait(NULL);
    return(0);
}
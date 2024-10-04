#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define NUM_CHILD 5
volatile sig_atomic_t count;

void handle_USR1 (int signo){
}

int main () {
    pid_t p[NUM_CHILD];
    int i,j;
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_NOCLDWAIT;
    act.sa_flags = SA_NOCLDSTOP;

    for (i = 0; i < NUM_CHILD; i++){
        p[i] = fork();
        if (p[i] == 0){
            for (j = i*200; j < (i+5)*200; j++){
                printf("Value: %d\n",j);
            }
            kill(getppid(),SIGUSR1);
            exit(0);
        }
    }
    for ( ; ; ){
        pause();
        if (p == 0){
            count--;
            if (count == 0){
                exit();
            }
        }
    }

    for (i = 0; i< NUM_CHILD; i++){
        waitpid(p[i],&status,0);
    }
    return(0);
} 
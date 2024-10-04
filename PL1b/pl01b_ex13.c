#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void taskA(){
}

void taskB(){
}

void taskC(){
}

int main(){
    pid_t p;
    int status;
    p = fork();
    if (p > 0){
        taskA();
        sleep(3);
        printf("Task A:done!");
        kill(getpid(),SIGUSR1);
        waitpid(getpid(), &status, 0);
        printf("Job is complete!");
    }
    if (p == 0){
        pause(); // Verificar se é necessário usar pause
        taskB();
        sleep(3);
        printf("Task B:done!");
        taskC();
        sleep(1);
        printf("Task C:done!");
        exit(0);
    }

}
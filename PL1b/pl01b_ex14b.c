#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define SIZE_STRING 100 
void handle_ALARM(int signo)
{
    kill(getppid(),9);
    char msg[80];
    sprintf(msg, "You were too slow and this program will end!\n");
    write(STDOUT_FILENO, msg, strlen(msg));
    exit(0);
}


int main(){
    char string[SIZE_STRING];
    int length;
    pid_t p;
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask);
    act.sa_handler = handle_ALARM;
    sigaction(SIGALRM, &act, NULL);
    p = fork();
    if (p > 0){
        printf("Write your string\n");
        scanf("%s",string);
        length = strlen(string);
        printf("Size of string:%d\n",length);
    }
    if (p == 0){
        sleep(10);
        kill(p,14);
    }
    return 0;
}
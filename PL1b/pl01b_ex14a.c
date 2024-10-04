#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define SIZE_STRING 100 

void handle_ALARM(int signo)
{
    char msg[80];
    sprintf(msg, "You were too slow and this program will end!\n");
    write(STDOUT_FILENO, msg, strlen(msg));
    exit(0);
}


int main(){
    char string[SIZE_STRING];
    int length;
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask); /* No signals blocked */
    act.sa_handler = handle_ALARM;
    sigaction(SIGALRM, &act, NULL);
    printf("Write your string\n");
    alarm(10);
    scanf("%s",string);
    length = strlen(string);
    printf("Size of string:%d\n",length);
    return 0;
}
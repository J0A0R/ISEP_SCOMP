#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_USR1(int signo)
{
    char msg[80];
    sprintf(msg, "I captured a SIGUSR1 sent by the process with PID %d\n",getpid());
    write(STDOUT_FILENO, msg, strlen(msg));
}
int main(int argc, char argv[]){
    pid_t pid;
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask); / No signals blocked /
    act.sa_handler = handle_USR1;
    sigaction(SIGUSR1, &act, NULL);
    kill(pid,10);
    / SIGUSR1 will now be captured and handled (ANSI C). /
    / (...) */
}
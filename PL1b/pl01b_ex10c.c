#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>

volatile sig_atomic_t USR1_counter;

void handle_USR1 (int signo){
    USR1_counter++;
    char msg[80];
    sprintf(msg, "SIGUSR1 signal captured: USR1 counter = %d\n",USR1_counter);
    write(STDOUT_FILENO, msg, strlen(msg));
    sleep(1);
}

int main () {
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask);
    //sigfillset(&act.sa_mask); /* No signals blocked */
    act.sa_handler = handle_USR1;
    act.sa_flags = SA_NODEFER;
    sigaction(SIGUSR1, &act, NULL);
    pid_t p;

    p = fork();
    if (p == 0) {
        sleep(1);
        for (int i=0; i<12; i++){
            kill(getppid(),SIGUSR1);
            usleep(10000);
        }

        //kill(getppid(), SIGINT);

        exit(0);
    }
    
    for( ; ; ) {
        printf ("I'm working!\n");
        sleep (1);
    }
} 
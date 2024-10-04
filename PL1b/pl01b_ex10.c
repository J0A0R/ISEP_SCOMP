#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t USR1_counter;

void handle_USR1 (int signo){
    USR1_counter++;
    char msg[80];
    sprintf(msg, "SIGUSR1 signal captured: USR1 counter = %d\n",USR1_counter);
    write(STDOUT_FILENO, msg, strlen(msg));
    sleep(2);
}

int main () {
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigfillset(&act.sa_mask); /* No signals blocked */
    act.sa_handler = handle_USR1;
    sigaction(SIGUSR1, &act, NULL);

    for( ; ; ) {
    printf ("I'm working!\n");
    sleep (1);
    }
} 
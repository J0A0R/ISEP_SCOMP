#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_quit (int signo){
    char msg[80];
    sprintf(msg, "I won't let the process end by pressing CTRL-\"!");
    write(STDOUT_FILENO, msg, strlen(msg));
}

int main () {
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask); /* No signals blocked */
    act.sa_handler = handle_quit;
    sigaction(SIGQUIT, &act, NULL);

    for( ; ; ) {
    printf ("I like signals\n");
    sleep (1);
    }
} 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_USR1 (int signo){
    sigset_t set;
    sigprocmask(SIG_BLOCK, NULL, &set);
    printf("Signals blocked:\n");
    for (int i = 1; i < NSIG; i++) {
        if (sigismember(&set, i)) {
            printf("%d\n", i);
        }
    }
}

int main () {
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigfillset(&act.sa_mask); /* No signals blocked */
    act.sa_handler = handle_USR1;
    sigaction(SIGINT, &act, NULL);

    for( ; ; ) {
    printf ("I'm working!\n");
    sleep (1);
    }
} 
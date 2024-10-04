#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NUM_CHILD 10

typedef struct {
    char message[30];
    int round;
} estrutura;

int main(void) {
    int fd[2];
    pid_t p[NUM_CHILD];
    int i;
    int round[NUM_CHILD];
    int status;
    estrutura p1,p2;

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    for (i = 0; i < NUM_CHILD; i++) {
        p[i] = fork();
        if (p[i] == 0) {
            close(fd[1]);
            read(fd[0], &p2, sizeof(p2));
            close(fd[0]);
            printf("%s\nRound: %d\n", p2.message, p2.round);
            exit(p2.round);
        }
    }

    close(fd[0]);
    for (i = 0; i < NUM_CHILD; i++) {
        sleep(2);
        strcpy(p1.message, "Win");
        p1.round = i + 1;
        write(fd[1], &p1, sizeof(p1));
    }
    close(fd[1]);

    for (i = 0; i < NUM_CHILD; i++) {
        waitpid(p[i], &status, 0);
        round[i] = WEXITSTATUS(status);
        printf("Pid: %d\nRound won: %d\n", p[i], round[i]);
    }
    return 0;
}


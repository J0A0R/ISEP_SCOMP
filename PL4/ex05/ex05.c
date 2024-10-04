#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SEM1_NAME "/sem1"
#define SEM2_NAME "/sem2"
#define SEM3_NAME "/sem3"

int main() {
    sem_t *sem1 = sem_open(SEM1_NAME, O_CREAT, 0644, 0);
    sem_t *sem2 = sem_open(SEM2_NAME, O_CREAT, 0644, 0);
    sem_t *sem3 = sem_open(SEM3_NAME, O_CREAT, 0644, 0);

    pid_t child1 = fork();
    if (child1 == 0) {
        // Child process 1
        printf("Sistemas ");
        fflush(stdout);
        sem_post(sem1);
        exit(0);
    }

    pid_t child2 = fork();
    if (child2 == 0) {
        // Child process 2
        sem_wait(sem1);
        printf("de ");
        fflush(stdout);
        sem_post(sem2);
        exit(0);
    }

    pid_t child3 = fork();
    if (child3 == 0) {
        // Child process 3
        sem_wait(sem2);
        printf("Computadores - ");
        fflush(stdout);
        sem_post(sem3);
        exit(0);
    }

    // Parent process
    sem_wait(sem3);
    printf("a melhor disciplina!\n");
    fflush(stdout);

    // Wait for all child processes to finish
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
    waitpid(child3, NULL, 0);

    // Clean up semaphores
    sem_close(sem1);
    sem_close(sem2);
    sem_close(sem3);
    sem_unlink(SEM1_NAME);
    sem_unlink(SEM2_NAME);
    sem_unlink(SEM3_NAME);

    return 0;
}

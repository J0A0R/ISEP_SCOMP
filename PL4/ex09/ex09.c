#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>

sem_t semaphore;

double getElapsedTime(struct timeval start, struct timeval end) {
    return (double)(end.tv_sec - start.tv_sec) * 1000000 + (double)(end.tv_usec - start.tv_usec);
}

void simulateWork(int time) {
    usleep(time);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s n time\n", argv[0]);
        return 1;
    }

    int numChildren, workTime;
    if (sscanf(argv[1], "%d", &numChildren) != 1 || sscanf(argv[2], "%d", &workTime) != 1) {
        printf("Invalid arguments.\n");
        return 1;
    }

    int i;
    pid_t childPid;
    struct timeval start, end;
    double elapsedTime;

    sem_init(&semaphore, 1, numChildren);

    gettimeofday(&start, NULL); // Start timing

    for (i = 0; i < numChildren; i++) {
        childPid = fork();
        if (childPid == 0) { // Child process
            sem_wait(&semaphore); // Wait for semaphore signal
            simulateWork(workTime);
            sem_post(&semaphore); // Release semaphore
            exit(0);
        } else if (childPid < 0) { // Fork error
            printf("Failed to create child process.\n");
            return 1;
        }
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    sem_destroy(&semaphore);

    gettimeofday(&end, NULL); // Stop timing

    elapsedTime = getElapsedTime(start, end);
    printf("Execution time: %.2f us\n", elapsedTime);

    return 0;
}

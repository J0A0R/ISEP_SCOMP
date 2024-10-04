#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *chips_sem;
sem_t *beer_sem;
sem_t *eat_sem;

void buy_chips() {
    // Simulate buying chips
    printf("Process %d is buying chips\n", getpid());
    sleep(1);
}

void buy_beer() {
    // Simulate buying beer
    printf("Process %d is buying beer\n", getpid());
    sleep(1);
}

void eat_and_drink() {
    // Simulate eating and drinking
    printf("Process %d is eating and drinking\n", getpid());
    sleep(1);
}

int main() {
    pid_t pid;
    int i;

    // Create named semaphores
    chips_sem = sem_open("/chips_sem", O_CREAT | O_EXCL, 0666, 0);
    beer_sem = sem_open("/beer_sem", O_CREAT | O_EXCL, 0666, 0);
    eat_sem = sem_open("/eat_sem", O_CREAT | O_EXCL, 0666, 0);

    for (i = 0; i < 6; i++) {
        pid = fork();
        if (pid == 0) {
            // Child process
            srand(getpid());

            if (i < 3) {
                // Process buys chips
                sleep(rand() % 5);
                buy_chips();
                sem_post(chips_sem);
            } else {
                // Process buys beer
                sleep(rand() % 5);
                buy_beer();
                sem_post(beer_sem);
            }

            sem_wait(eat_sem);
            eat_and_drink();

            exit(0);
        }
    }

    // Parent process
    for (i = 0; i < 3; i++) {
        sem_wait(chips_sem);
    }

    for (i = 0; i < 3; i++) {
        sem_wait(beer_sem);
    }

    for (i = 0; i < 6; i++) {
        sem_post(eat_sem);
    }

    for (i = 0; i < 6; i++) {
        wait(NULL);
    }

    // Close and unlink semaphores
    sem_close(chips_sem);
    sem_close(beer_sem);
    sem_close(eat_sem);
    sem_unlink("/chips_sem");
    sem_unlink("/beer_sem");
    sem_unlink("/eat_sem");

    return 0;
}

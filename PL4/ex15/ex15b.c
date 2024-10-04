#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CAPACITY 10
#define SEMAPHORE_NAME "/club_semaphore"

typedef enum {
    VIP,
    SPECIAL,
    NORMAL
} ClientType;

void clientProcess(ClientType type, int stayDuration, sem_t* semaphore, int clientNum) {
    sleep(stayDuration);

    sem_wait(semaphore);  // Acquire the semaphore

    // Critical section - entering the club
    printf("Client %d (Type: %s) entered the club.\n", clientNum, (type == VIP) ? "VIP" : (type == SPECIAL) ? "Special" : "Normal");

    // Simulating some activity inside the club
    sleep(2);

    // Critical section - leaving the club
    printf("Client %d (Type: %s) left the club.\n", clientNum, (type == VIP) ? "VIP" : (type == SPECIAL) ? "Special" : "Normal");

    sem_post(semaphore);  // Release the semaphore

    exit(0);
}

int main() {
    sem_unlink(SEMAPHORE_NAME);  // Unlink the semaphore if it already exists
    sem_t* semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, MAX_CAPACITY);  // Open or create the semaphore

    int clientNum = 1;  // Variable to keep track of client numbers

    while (1) {
        int randomAction = rand() % 3;  // Randomly choose 0, 1, or 2 for client type

        if (randomAction == 0) {
            // VIP client
            pid_t pid = fork();
            if (pid == 0) {
                clientProcess(VIP, rand() % 6 + 5, semaphore, clientNum);
            } else if (pid > 0) {
                printf("Created VIP client process: %d\n", pid);
                clientNum++;
            }
        } else if (randomAction == 1) {
            // Special client
            pid_t pid = fork();
            if (pid == 0) {
                clientProcess(SPECIAL, rand() % 6 + 5, semaphore, clientNum);
            } else if (pid > 0) {
                printf("Created Special client process: %d\n", pid);
                clientNum++;
            }
        } else {
            // Normal client
            pid_t pid = fork();
            if (pid == 0) {
                clientProcess(NORMAL, rand() % 6 + 5, semaphore, clientNum);
            } else if (pid > 0) {
                printf("Created Normal client process: %d\n", pid);
                clientNum++;
            }
        }

        // Simulating some delay between creating clients
        sleep(1);
    }

    // Waiting for child processes to finish
    while (wait(NULL) > 0);

    sem_close(semaphore);  // Close the semaphore
    sem_unlink(SEMAPHORE_NAME);  // Unlink the semaphore

    return 0;
}

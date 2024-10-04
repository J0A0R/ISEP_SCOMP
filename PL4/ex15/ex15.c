#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAX_CAPACITY 10
#define SEMAPHORE_NAME "/club_semaphore"

int main() {
    sem_unlink(SEMAPHORE_NAME);  // Unlink the semaphore if it already exists
    sem_t* semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, MAX_CAPACITY);  // Open or create the semaphore

    int arrivalOrder = 1;  // Variable to keep track of arrival order
    int numClients = 0;  // Variable to keep track of the number of clients inside the club

    while (1) {
        int randomAction = rand() % 2;  // Randomly choose 0 or 1 for entrance or exit

        if (randomAction == 0) {
            sem_wait(semaphore);  // Acquire the semaphore

            // Critical section - entering the club
            printf("Client %d entered the club.\n", arrivalOrder++);
            numClients++;

            // Simulating some activity inside the club
            // ...
            sleep(2);

        } else {
            if (numClients > 0){
                sem_post(semaphore);  // Acquire the semaphore

                // Critical section - leaving the club
                printf("Client left the club.\n");
                numClients--;
        }
        }

        // Simulating some delay between actions
        sleep(1);
    }

    sem_close(semaphore);  // Close the semaphore
    sem_unlink(SEMAPHORE_NAME);  // Unlink the semaphore

    return 0;
}

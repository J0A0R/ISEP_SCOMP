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


#define SHARED_MEMORY_NAME "/ticket_shared_memory"
#define SHARED_MEMORY_SIZE sizeof(int)

int main() {
    // Create or open the shared memory object
    int sharedMemoryDescriptor = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (sharedMemoryDescriptor == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size of the shared memory object
    if (ftruncate(sharedMemoryDescriptor, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map the shared memory object into the process's address space
    int* ticketNumber = (int*)mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryDescriptor, 0);
    if (ticketNumber == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize the ticket number
    *ticketNumber = 1;

    // Create a semaphore for synchronization
    sem_t* semaphore = sem_open("/ticket_semaphore", O_CREAT | O_EXCL, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Simulate selling tickets
    while (1) {
        // Wait for a client to request a ticket
        sem_wait(semaphore);

        // Serve the client by providing the ticket number
        int clientTicketNumber = *ticketNumber;
        *ticketNumber += 1;

        // Release the semaphore
        sem_post(semaphore);

        // Print the ticket number for the client
        printf("Seller: Ticket number %d sold to client.\n", clientTicketNumber);
        fflush(stdout);

        // Wait for a random amount of time to simulate serving the client
        int serveTime = 1 + (rand() % 10);
        sleep(serveTime);
    }

    // Unmap the shared memory object
    if (munmap(ticketNumber, SHARED_MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    // Close and unlink the shared memory object
    close(sharedMemoryDescriptor);
    shm_unlink(SHARED_MEMORY_NAME);

    // Close and unlink the semaphore
    sem_close(semaphore);
    sem_unlink("/ticket_semaphore");

    return 0;
}

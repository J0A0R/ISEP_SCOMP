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
    // Open the shared memory object
    int sharedMemoryDescriptor = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);
    if (sharedMemoryDescriptor == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map the shared memory object into the process's address space
    int* ticketNumber = (int*)mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryDescriptor, 0);
    if (ticketNumber == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Create a semaphore for synchronization
    sem_t* semaphore = sem_open("/ticket_semaphore", 0);
    if (semaphore == SEM_FAILED) {
    perror("sem_open");
    exit(1);
    }

    // Request a ticket from the seller
    sem_wait(semaphore);

    // Get the ticket number from the shared memory
    int clientTicketNumber = *ticketNumber;

    // Update the ticket number in the shared memory
    *ticketNumber += 1;

    // Release the semaphore
    sem_post(semaphore);

    // Print the ticket number for the client
    printf("Client: Ticket number %d received.\n", clientTicketNumber);
    fflush(stdout);

    // Unmap the shared memory object
    if (munmap(ticketNumber, SHARED_MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    // Close the shared memory object
    close(sharedMemoryDescriptor);

    return 0;
}

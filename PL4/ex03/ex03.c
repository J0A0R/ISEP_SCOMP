#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <errno.h>  // Include errno header

#define MAX_STRINGS 50
#define MAX_CHARS 80
#define SHARED_MEM_NAME "/my_shared_memory"
#define SEMAPHORE_NAME "/my_semaphore"
#define REMOVE_PROBABILITY 30
#define MAX_WAIT_TIME_SECONDS 12

typedef struct {
    char strings[MAX_STRINGS][MAX_CHARS];
    int count;
} SharedMemory;

extern int errno;  // Declare errno as an external variable

void writeToSharedMemory(SharedMemory* sharedMemory, pid_t pid, sem_t* semaphore) {
    if (sharedMemory->count >= MAX_STRINGS) {
        printf("Shared memory limit reached. Terminating.\n");
        exit(0);
    }

    int remove_last = (rand() % 100) < REMOVE_PROBABILITY;
    if (remove_last && sharedMemory->count > 0) {
        printf("PID %d is removing the last written string.\n", pid);
        sharedMemory->count--;
    } else {
        int index = sharedMemory->count;
        sprintf(sharedMemory->strings[index], "I'm the Father - with PID %d", pid);
        sharedMemory->count++;
        printf("PID %d wrote: %s\n", pid, sharedMemory->strings[index]);
    }

    sem_post(semaphore);
}

int main() {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, sizeof(SharedMemory)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    SharedMemory* sharedMemory = (SharedMemory*)mmap(NULL, sizeof(SharedMemory),
                                                     PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(shm_fd);

    sem_t* semaphore = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    sharedMemory->count = 0;

    srand(time(NULL));
    pid_t pid = getpid();

    struct timespec wait_time;
    wait_time.tv_sec = MAX_WAIT_TIME_SECONDS;
    wait_time.tv_nsec = 0;

    while (1) {
        int sem_result = sem_timedwait(semaphore, &wait_time);

        if (sem_result == -1) {
            if (errno == EINTR) {
                printf("PID %d missed the deadline to access the shared memory.\n", pid);
                continue;
            } else {
                perror("sem_timedwait");
                exit(1);
            }
        }

        writeToSharedMemory(sharedMemory, pid, semaphore);
        wait_time.tv_sec = MAX_WAIT_TIME_SECONDS;
        wait_time.tv_nsec = 0;
    }

    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);

    if (munmap(sharedMemory, sizeof(SharedMemory)) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_STRINGS 50
#define MAX_CHARS 80
#define SHARED_MEM_NAME "/my_shared_memory"

typedef struct {
    char strings[MAX_STRINGS][MAX_CHARS];
    int count;
} SharedMemory;

void writeToSharedMemory(SharedMemory* sharedMemory, pid_t pid) {
    if (sharedMemory->count >= MAX_STRINGS) {
        printf("Shared memory limit reached. Terminating process %d.\n", pid);
        exit(0);
    }

    int index = sharedMemory->count;
    sprintf(sharedMemory->strings[index], "I'm the Father - with PID %d", pid);
    sharedMemory->count++;

    printf("PID %d wrote: %s\n", pid, sharedMemory->strings[index]);
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

    sharedMemory->count = 0;

    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            pid_t child_pid = getpid();
            while (1) {
                writeToSharedMemory(sharedMemory, child_pid);
                sleep(rand() % 5 + 1);
            }
            exit(0);
        }
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    if (shm_unlink(SHARED_MEM_NAME) == -1) {
        perror("shm_unlink");
        exit(1);
    }

    return 0;
}

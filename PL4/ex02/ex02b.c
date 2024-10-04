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

void printSharedMemory(SharedMemory* sharedMemory) {
    printf("Current lines in shared memory:\n");
    for (int i = 0; i < sharedMemory->count; i++) {
        printf("%s\n", sharedMemory->strings[i]);
    }
    printf("Total number of lines: %d\n", sharedMemory->count);
}

int main() {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    SharedMemory* sharedMemory = (SharedMemory*)mmap(NULL, sizeof(SharedMemory),
                                                     PROT_READ, MAP_SHARED, shm_fd, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(shm_fd);

    printSharedMemory(sharedMemory);

    if (munmap(sharedMemory, sizeof(SharedMemory)) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}

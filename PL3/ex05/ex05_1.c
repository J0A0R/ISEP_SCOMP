#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct {
    int value;
} shared_data;

volatile sig_atomic_t flag = 0;

void handler(int signum) {
    flag = 1;
}

int main() {
    int fd, data_size = sizeof(shared_data);
    shared_data *shared_memory;

    // Create shared memory area
    fd = shm_open("/myshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }

    // Resize shared memory to fit struct
    ftruncate(fd, data_size);

    // Map shared memory to process memory space
    shared_memory = mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("Error mapping shared memory to process");
        exit(EXIT_FAILURE);
    }

    // Initialize shared data to 100
    shared_memory->value = 100;

    // Register signal handler
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        exit(EXIT_FAILURE);
    }

    // Create child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        for (int i = 0; i < 1000000; i++) {
            while (!flag); // Wait for signal from parent
            shared_memory->value++; // Increment shared value
            flag = 0; // Reset flag
            kill(getppid(), SIGUSR1); // Signal parent
        }
        exit(EXIT_SUCCESS);
    } else { // Parent process
        for (int i = 0; i < 1000000; i++) {
            shared_memory->value--; // Decrement shared value
            kill(pid, SIGUSR2); // Signal child
            while (!flag); // Wait for signal from child
            flag = 0; // Reset flag
        }
        printf("Final value: %d\n", shared_memory->value);
        wait(NULL);
    }

    // Cleanup
    if (munmap(shared_memory, data_size) == -1) {
        perror("Error unmapping shared memory from process");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink("/myshm") == -1) {
        perror("Error removing shared memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}

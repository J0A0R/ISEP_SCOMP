#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define MAX_VALUES 30

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t mutex;
    sem_t empty;
    sem_t full;
} shared_data;

void producer(shared_data* data) {
    for (int i = 0; i < MAX_VALUES; i++) {
        sem_wait(&data->empty);
        sem_wait(&data->mutex);

        data->buffer[data->in] = i;
        data->in = (data->in + 1) % BUFFER_SIZE;
        printf("Producer produced value %d\n", i);

        sem_post(&data->mutex);
        sem_post(&data->full);
    }
}

void consumer(shared_data* data) {
    for (int i = 0; i < MAX_VALUES; i++) {
        sem_wait(&data->full);
        sem_wait(&data->mutex);

        int value = data->buffer[data->out];
        data->out = (data->out + 1) % BUFFER_SIZE;
        printf("Consumer consumed value %d\n", value);

        sem_post(&data->mutex);
        sem_post(&data->empty);
    }
}

int main() {
    // Create shared memory segment
    int fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("Error creating shared memory segment");
        exit(1);
    }
    if (ftruncate(fd, sizeof(shared_data)) == -1) {
        perror("Error resizing shared memory segment");
        exit(1);
    }
    shared_data* data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("Error mapping shared memory segment");
        exit(1);
    }

    // Initialize shared data
    data->in = 0;
    data->out = 0;
    sem_init(&data->mutex, 1, 1);
    sem_init(&data->empty, 1, BUFFER_SIZE);
    sem_init(&data->full, 1, 0);

    // Create child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating child process");
        exit(1);
    } else if (pid == 0) {
        // Child process is the consumer
        consumer(data);
        exit(0);
    } else {
        // Parent process is the producer
        producer(data);
    }

    // Clean up
    munmap(data, sizeof(shared_data));
    close(fd);
    shm_unlink("/shared_memory");
    sem_destroy(&data->mutex);
    sem_destroy(&data->empty);
    sem_destroy(&data->full);

    return 0;
}

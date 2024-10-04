#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>


typedef struct
{
    int number;
} arraypartilha;


void handle_USR1(int signo)
{
    
}


int main() {
    int fd, data_size = sizeof(arraypartilha);
    int media;
    arraypartilha *estrut;
    fd = shm_open("/shmtest", O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, data_size);
    estrut = (arraypartilha *)mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (fd == -1) {
        printf("Error at shm_open()!\n");
        exit(EXIT_FAILURE);
    }


    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask); / No signals blocked /
    act.sa_handler = handle_USR1;
    sigaction(SIGUSR1, &act, NULL);



    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        for (int i = 0; i < 1000000; i++) {
            kill(getppid(), SIGUSR1);
        }
        exit(0);
    } else {  // Parent process
        for (int i = 0; i < 1000000; i++) {
            kill(pid, SIGUSR2);
        }

        printf("Current value: %d\n", *shm_ptr);

        wait(NULL);
        shm_unlink(SHM_NAME);
    }



    
    if (munmap((void *)estrut, data_size) < 0) {
        printf("Error at munmap()!\n");
        exit(EXIT_FAILURE);
    }

    // Close file descriptor
    if (close(fd) < 0) {
        printf("Error at close()!\n");
        exit(EXIT_FAILURE);
    }

    // Remove file from system
    if (shm_unlink("/shmtest") < 0) {
        printf("Error at shm_unlink()!\n");
        exit(EXIT_FAILURE);
    }


    return 0;
}

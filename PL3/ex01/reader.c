#include "pl03_ex01.h"

int main()
{
    int fd, data_size = sizeof(estudante);
    estudante *estrut;
    fd = shm_open("/shmtest", O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, data_size);
    estrut = (estudante *)mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (fd == -1) {
        printf("Error at shm_open()!\n");
        exit(EXIT_FAILURE);
    }

    printf("\n===========================================\n");

    // Print the data
    printf("Número do estudante: %d\n", estrut->number);
    printf("Nome do estudante: %s\n", estrut->name);
    printf("Morada: %s\n", estrut->address);

    printf("===========================================\n");

    

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
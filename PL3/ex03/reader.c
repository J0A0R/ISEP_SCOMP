#include "pl03_ex03.h"

int main()
{
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

    printf("\n===========================================\n");

    // Print the data
    for(int i=0;i<10;i++){
    printf("Número de estudante: %d\n", estrut->number[i]);
    media = media + estrut->number[i];
    }
    printf("Média: %d\n",media/10);
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
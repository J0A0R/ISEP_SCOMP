#include "pl03_ex01.h"

int main(){
    int fd, data_size = sizeof(estudante);
    estudante *estrut;
    if (fd == -1)
    {
     printf("Error at shm_open()!\n");
        exit(EXIT_FAILURE);
    }


    fd = shm_open("/shmtest", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, data_size);
    estrut = (estudante*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    printf("Número do estudante: \n");
    scanf("%d", &estrut->number);

    printf("Nome do estudante: \n");
    scanf("%s", &estrut->name);

    printf("Morada: \n");
    scanf("%s", &estrut->address);

        // Undo mapping
    if (munmap((void *)estrut, data_size) < 0) {
        printf("Error at munmap()!\n");
        exit(EXIT_FAILURE);
    }


    // Close file descriptor
    if (close(fd) < 0) {
        printf("Error at close()!\n");
        exit(EXIT_FAILURE);
    }
 
    return 0;


}


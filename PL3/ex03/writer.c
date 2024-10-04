#include "pl03_ex03.h"


int main(){
    int fd, data_size = sizeof(arraypartilha);
    time_t t;
    arraypartilha *estrut;
    if (fd == -1)
    {
     printf("Error at shm_open()!\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned) time(&t));

    fd = shm_open("/shmtest", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, data_size);
    estrut = (arraypartilha*)mmap(NULL,data_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

     for(int i=0;i<10;i++){
        estrut->number[i]= (rand() % 20) + 1;
    }

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

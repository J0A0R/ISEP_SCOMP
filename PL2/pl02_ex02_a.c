#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 80

    int main(void){
    char read_msg[BUFFER_SIZE];
    char write_msg[BUFFER_SIZE];
    int read_nr;
    int write_nr;
    int fd[2];
    pid_t p;
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }


    p = fork();

    if (p > 0)
    {
        close(fd[0]);
        printf("Insira a frase: \n");
        scanf("%s", write_msg);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        printf("Insira o número: \n");
        scanf("%d", &write_nr);
        write(fd[1], &write_nr, sizeof(write_nr));
        close(fd[1]);
        
        }

    if (p == 0)
    {
        close(fd[1]);
        read(fd[0], read_msg, BUFFER_SIZE);
        sleep(2);
        printf("\nFrase: %s\n", read_msg);
        read(fd[0], &read_nr, sizeof(read_nr));
        printf("Número: %d\n",read_nr);
        close(fd[0]);
    }
       
}
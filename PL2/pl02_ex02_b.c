#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 80
typedef struct {
    char message [BUFFER_SIZE]; 
    int numero; 
} estrutura ;


    int main(void){
    estrutura p1;
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
        printf("Insira o número: \n");
        scanf("%d", &write_nr);
        strcpy(p1.message,write_msg);
        p1.numero = write_nr;
        write(fd[1], &p1, sizeof(p1));
        close(fd[1]);
        
        }

    if (p == 0)
    {
        close(fd[1]);
        read(fd[0], &p1, sizeof(p1));
        printf("Frase: %s\n",p1.message);
        printf("Número: %d\n",p1.numero);
        close(fd[0]);
    }
       
}
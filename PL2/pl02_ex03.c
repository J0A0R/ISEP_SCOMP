#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 80
typedef struct {
    char message [BUFFER_SIZE]; 
    char message2 [BUFFER_SIZE];
} estrutura ;


    int main(void){
    estrutura p1;
    strcpy(p1.message, "Hello World!");
    strcpy(p1.message2, "Goodbye!");
    int fd[2];
    pid_t p;
    int status;
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }


    p = fork();

    if (p > 0)
    {
        close(fd[0]);
        write(fd[1], &p1, sizeof(p1));
        close(fd[1]);
        waitpid(p,&status,0);
        printf("Pid: %d\n",p);
        int saida = WEXITSTATUS(status);
        printf("Valor de saída: %d\n",saida);
        }

    if (p == 0)
    {
        close(fd[1]);
        read(fd[0], &p1, sizeof(p1));
        printf("Mensagem 1: %s\n",p1.message);
        printf("Mensagem 2: %s\n",p1.message2);
        close(fd[0]);
        exit(3);

    }
       
}
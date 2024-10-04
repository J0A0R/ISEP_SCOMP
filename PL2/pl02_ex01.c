#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


    int main(void){
    pid_t read_msg[8];
    pid_t write_msg[8];
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
        printf("PID do pai: %d\n",getpid());
        write_msg[0] = getpid();
        write(fd[1],write_msg,sizeof(read_msg) / sizeof(int));
        close(fd[1]);
        
        }

    if (p == 0)
    {
        close(fd[1]);
        read(fd[0], read_msg, 8);
        printf("Filho leu pid do pai: %d\n", read_msg[0]);
        close(fd[0]);
        exit(0);
    }
       
}
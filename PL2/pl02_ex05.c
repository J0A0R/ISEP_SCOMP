#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 256
    int main(void){
    char read_msg[BUFFER_SIZE];
    char write_msg[BUFFER_SIZE];
    char read_msg2[BUFFER_SIZE];
    char write_msg2[BUFFER_SIZE];
    int pipe1[2];
    int pipe2[2];
    pid_t p;
    int i;
    if(pipe(pipe1) == -1){
        perror("Pipe failed");
        return 1;
    }
    if(pipe(pipe2) == -1){
        perror("Pipe failed");
        return 1;
    }
    p = fork();
    if (p > 0)
    {
        close(pipe1[1]);
        read(pipe1[0], read_msg,BUFFER_SIZE);
        printf("Mensagem lida:%s\n",read_msg);
        close(pipe1[0]);
        close(pipe2[0]);
        if(isupper(read_msg[0])){
            for(int i=0;i<strlen(read_msg);i++){
            write_msg2[i] = tolower(read_msg[i]);
            }
        }else {
            for(int i=0;i<strlen(read_msg);i++){
            write_msg2[i] = toupper(read_msg[i]);
            } 
        }
        write(pipe2[1],write_msg2,strlen(write_msg2)+1);
        close(pipe2[1]);
    }
    if (p == 0)
    {
        close(pipe1[0]);
        printf("Insira a frase pretendida:\n");
        scanf("%s", write_msg);
        write(pipe1[1],write_msg,strlen(write_msg)+1);
        close(pipe1[1]);
        close(pipe2[1]);
        read(pipe2[0], read_msg2,BUFFER_SIZE);
        printf("Mensagem recebida:%s\n",read_msg2);
        close(pipe2[0]);

    }

}

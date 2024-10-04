#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<sys/wait.h>


#define ARRAY_SIZE 1000
typedef struct {
    int temps [5];
} estrutura ;

    int main(void){
    estrutura p1;
    int fd[2];
    pid_t p[5];
    int temp_alt;
    int i, j, k;
    time_t t;
    int temp_total;
    int vec1 [ARRAY_SIZE]; 
    int vec2 [ARRAY_SIZE];
    int status;
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }
    srand ((unsigned) time (&t));
    for (i = 0; i < ARRAY_SIZE; i++){
        vec1[i] = rand () % 1000;
        vec2[i] = rand () % 1000;
    }
    for (i = 0; i < 5; i++){
    p[i] = fork();
    if (p[i] == 0){
        for(int j = i * 200; j <= (i + 1) * 200; j++){
            temp_alt += vec1[j] + vec2[j];
        }
        close(fd[0]);
        p1.temps[i] = temp_alt;
        write(fd[1], &p1, sizeof(p1));
        close(fd[1]);
        exit(0);
    }
    }
    for (i = 0; i < 5; i++){
        waitpid(p[i],&status,0);
    }
    for (i = 0; i < 5; i++){
        close(fd[1]);
        read(fd[0], &p1, sizeof(p1));
        temp_total += p1.temps[i];
        close(fd[0]);
    }
    printf("Valor total: %d\n",temp_total);
    return 0;
}
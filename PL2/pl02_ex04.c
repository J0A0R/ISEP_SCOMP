#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd[2];
    pid_t p;
    char buffer[BUFFER_SIZE];
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }
    p = fork();

    if (p > 0) {
        FILE* file = fopen("file.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
        while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
            write(fd[1], buffer, BUFFER_SIZE);
        }
        close(fd[1]);
        waitpid(p, NULL, 0);
    } 
    if (p == 0) {
        close(fd[1]);
        while (read(fd[0], buffer, BUFFER_SIZE) > 0) {
            printf("%s", buffer);
        }
        close(fd[0]);
        exit(0);
    }
    return 0;
}
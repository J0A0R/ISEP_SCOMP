#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void){
    pid_t p1, p2;
    int status;
    p1 = fork();
    if (p1 == 0)
    {
        sleep(1);
        exit(1);
    }
    p2 = fork();
    if (p2 == 0)
    {
        sleep(2);
        exit(2);
    }
    waitpid(p1, &status, 0);
    printf("Child process 1 exited with status %d\n", WEXITSTATUS(status));
    waitpid(p2, &status, 0);
    printf("Child process 2 exited with status %d\n", WEXITSTATUS(status));
    return 0;
}
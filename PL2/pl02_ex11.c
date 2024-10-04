#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <sys/wait.h>

#define NUMBER_OF_CHILDREN 5
#define NUMBER_OF_PIPES 6

int main(){
    int pipes[NUMBER_OF_PIPES][2];

    int i;
    for (i = 0; i < NUMBER_OF_PIPES; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("Pipe failed!");
            exit(-1);
        }
    }

    pid_t p[NUMBER_OF_CHILDREN];
    int value, random;
    for(i=0; i<NUMBER_OF_CHILDREN; i++){
        p[i]=fork();
        if(p[i]==0){
            srand((unsigned)time(NULL) * getpid());
            close(pipes[i][1]);
            read(pipes[i][0], &value, sizeof(value));
            random = rand() % (1 + 500) + 1;
            printf("pid: %d, random number: %d\n", getpid(), random);
            
            close(pipes[i][0]);
			close(pipes[i+1][0]);

            if(random > value){
                write(pipes[i+1][1],&random,sizeof(random));  
            }else{
                write(pipes[i+1][1],&value,sizeof(value));
            }

            close(pipes[i+1][1]);
			exit(0);
        }
    }
    srand((unsigned)time(NULL) * getpid());
    random = rand() % (1 + 500) + 1;
    printf("(PARENT) pid: %d, random number: %d\n", getpid(), random);

    close(pipes[0][0]);
	write(pipes[0][1],&random,sizeof(random));
	close(pipes[0][1]);

	close(pipes[NUMBER_OF_CHILDREN][1]);
	read(pipes[NUMBER_OF_CHILDREN][0],&value,sizeof(value));
	close(pipes[NUMBER_OF_CHILDREN][0]);

	printf("Biggest number: %d\n",value);
    return 0;
}
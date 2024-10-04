#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<sys/wait.h>


#define ARRAY_SIZE 50000
#define NUM_CHILD 10
#define CHILD_SIZE 5000

typedef struct {
    int customer_code;
    int product_code;
    int quantity;
} estrutura ;

    int main(void){
    estrutura sales[ARRAY_SIZE];
    int product_size,i,j,status,product_read,product_write;
    product_size =  0;
    int products[product_size];
    int fd[2];
    pid_t p[NUM_CHILD];
    time_t t;

    //Create pipe
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }

    //Generate random values
    srand ((unsigned) time (&t));
    for (i = 0; i < ARRAY_SIZE; i++){
        sales[i].customer_code = rand () % 1000;
        sales[i].product_code = i;
        sales[i].quantity = rand() % 25;
    }

    //Create child processes
    for (i = 0; i < NUM_CHILD; i++){
    p[i] = fork();
    if (p[i] == 0){
        for(int j = i * CHILD_SIZE; j < (i + 1) * CHILD_SIZE; j++){
            if (sales[j].quantity > 20){
                close(fd[0]);
                product_write = sales[j].product_code;
                write(fd[1],&product_write,sizeof(product_write));
                close(fd[1]);
            }
        }
        exit(0);
    }
    }

    close(fd[1]);
    for (i = 0; i < NUM_CHILD; i++){
        while (read(fd[0],&product_read, sizeof(product_read)) > 0) {
            products[product_size++] = product_read;
        }
    }
    close(fd[0]);

    for (i = 0; i < NUM_CHILD; i++){
        waitpid(p[i],&status,0);
    }

    for (i < 0; i < product_size; i++){
        printf("Product code: %d\n",products[i]);
    }
    return 0;
}
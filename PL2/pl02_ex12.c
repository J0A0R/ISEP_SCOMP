#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 3
#define NUM_CHILD 5

typedef struct
{
    int code;
    char name[30];
    float preco;
} produto;

produto p1[ARRAY_SIZE];

int main(void)
{
    int i,code,code2;
    produto p2;
    int pipe1[2];
    int pipe2[2];
    pid_t p[5];
    time_t t;
    srand((unsigned)time(&t));
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        p1[i].code = i + 1;
        p1[i].preco = rand() % 10;
    }
    strcpy(p1[0].name, "Cebola");
    strcpy(p1[1].name, "Tomate");
    strcpy(p1[2].name, "Batata");
    if (pipe(pipe1) == -1)
    {
        perror("pipe");
        exit(1);
    }
    if (pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(1);
    }
    for (i = 0; i < NUM_CHILD; i++)
    {
        code = rand() % 3 + 1;
        p[i] = fork();
        if (p[i] == 0)
        {
            close(pipe1[0]);
            write(pipe1[1], &code, sizeof(code));
            close(pipe1[1]);
            close(pipe2[1]);
            read(pipe2[0], &p2, sizeof(p2));
            close(pipe2[0]);
            if (p2.preco != 0){
                printf("Nome: %s Preço: %f\n", p2.name, p2.preco);
            
            }
            exit(0);
        }
    }

    close(pipe1[1]);
    close(pipe2[0]);
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        read(pipe1[0], &code2, sizeof(code2));
        if (code2 == p1[i].code)
        {
            strcpy(p2.name, p1[i].name);
            p2.preco = p1[i].preco;
            write(pipe2[1], &p2, sizeof(p2));
        }
    }
    close(pipe1[0]);
    close(pipe2[1]);
    return 0;
}
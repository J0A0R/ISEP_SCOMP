#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

typedef struct
{
    int nova_aposta;
    int credito;
} estrutura;

int main(void)
{
    estrutura p1;
    int pipe1[2];
    int pipe2[2];
    pid_t p;
    time_t t;
    int i,aposta,random_nr;

    if (pipe(pipe1) == -1)
    {
        perror("Pipe failed");
        return 1;
    }
    if (pipe(pipe2) == -1)
    {
        perror("Pipe failed");
        return 1;
    }

    p = fork();

    if (p > 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);
        srand((unsigned)time(&t) % getpid());
        p1.credito = 20;
        // PIPE 1 ESCRITA PAI
        // PIPE 2 LEITURA PAI
        while (p1.credito > 0)
        {
            random_nr = (rand() % 5) + 1;
            p1.nova_aposta = 1;
            write(pipe1[1],&p1, sizeof(p1));
            read(pipe2[0],&p1,sizeof(p1));
            if (p1.nova_aposta == random_nr)
            {
                p1.credito += 10;
                printf("Acertou!\n");
            }
            else {
                p1.credito -= 5;
                printf("Errou!\n");
            }
            write(pipe1[1],&p1,sizeof(p1));
        }

        p1.nova_aposta = 0;
        write(pipe1[1],&p1, sizeof(p1));

        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    }

    if (p == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        while (1)
        {

            // PIPE 1 LEITURA FILHO
            // PIPE 2 ESCRITA FILHO
            read(pipe1[0],&p1, sizeof(p1));

            if (p1.nova_aposta == 0)
            {
                printf("Não pode efetuar nova aposta, não tem crédito suficiente!\n");
                close(pipe2[1]);
                exit(0);
            }

            printf("Pode efetuar uma nova aposta! \n");
            printf("Tem neste momento %d euros!\n", p1.credito);
            aposta = (rand() % 5) + 1;
            p1.nova_aposta = aposta;
            write(pipe2[1],&p1, sizeof(p1));

            read(pipe1[0],&p1, sizeof(p1));
            printf("O meu novo saldo é: %d\n", p1.credito);
        }
    }
}
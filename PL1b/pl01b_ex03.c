#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(){
    pid_t p;
    int sinal;
    printf("Qual é o pid do processo a matar: \n");
    scanf("%d",&p);
    printf("Qual é o sinal: \n");
    scanf("%d",&sinal);
    kill(p,sinal);
}
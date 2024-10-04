# README #

Realizado por:
1210817- João Rodrigues
1210821- Mateus Fernandes

Neste documento iremos apresentar a resolução dos exercícios das fichas PL, a nossa approach/justificação e o grau de confiança para cada exercício.

## Definição de grau de confiança ##

1 - Muito pouco
2- Pouco
3- Mediano
4- Confortável 
5- Muito confortável

## PL1 ##

### Ex1

### a)
Presente no ficheiro pl01b_ex01.c

No terminal inserimos o comando kill -l, e verificamos os sinais que existem. 
1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX

Grau de confiança: 5


### Ex2

Presente no ficheiro pl01b_ex02.c

### a)
Executando o programa, observamos que o programa fica num ciclo infinito a imprimir na consola a frase "I love SCOMP!".

Grau de confiança: 5

### b) 

Após executar o programa e correr no terminal o comando "ps", observamos que o pid do processo é ... (número que varia de acordo com a máquina e o número de processos que já foram iniciados antes da execução do programa).

Grau de confiança: 5

### c)

Enviando o comando kill -s STOP PID, é possível parar a execução do processo, uma vez que lhe é enviado um SIGSTOP.

Grau de confiança: 5

### d)

Após executarmos o comando ps -l, na consola, podemos verificar que no estado do processo referente ao exercício em execução, encontrava-se um "T", que significa STOPPED, tal como era esperado.

Grau de confiança: 5

### e)

Após executarmos o comando CONT, o processo continuou a sua execução e o seu estado passou a "R", que significa RUNNING.

Grau de confiança: 5 


### Ex3

Presente no ficheiro pl01b_ex03.c

Para a resolução deste exercício, perguntamos ao utilizador, qual é o PID do processo para o qual queremos enviar um sinal, e após isso, escolhemos o número do sinal a enviar consoante o sinal que é pretendido enviar. Podemos observar através da lista presente no Ex1, quais os sinais que estão disponíveis para ser enviados.

Grau de confiança: 5

### Ex4 

### a) 

O sinal sigaction() é melhor, por ser mais recente e mais compatível com qualquer distribuição do linux. Para além disso, o sigaction recebe mais parâmetros que o signal, o que permite uma melhor configuração do sinal a ser enviado, guardar o estado do processo e o que o sinal fará após ter sido enviado.

Grau de confiança: 4

### b)

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
- int signum, trata-se do sinal em si, pode ser qualquer um exceto o SIGKILL ou SIGSTOP
- *act pode ser um apontador null ou não. Caso o seja, o sinal irá ativar o seu comportamento default, caso o apontador seja diferente de null, o sinal irá ativar o seu comportamento, consoante o conteúdo presente na estrutura
- *oldact, trata-se de um apontador que aponta para um registo de memória que guarda o atual comportamento do sigaction. Se o apontador for null, esta informação não é guardada


Grau de confiança: 3

### Ex5

# Number  Signal  Default     Comment                              POSIX
    Name            Action

 1 SIGHUP     Terminate   Hang up controlling terminal or      Yes
                          process 
 2 SIGINT     Terminate   Interrupt from keyboard, Control-C   Yes
 3 SIGQUIT    Dump        Quit from keyboard, Control-\        Yes
 4 SIGILL     Dump        Illegal instruction                  Yes
 5 SIGTRAP    Dump        Breakpoint for debugging             No
 6 SIGABRT    Dump        Abnormal termination                 Yes
 6 SIGIOT     Dump        Equivalent to SIGABRT                No
 7 SIGBUS     Dump        Bus error                            No
 8 SIGFPE     Dump        Floating-point exception             Yes
 9 SIGKILL    Terminate   Forced-process termination           Yes
10 SIGUSR1    Terminate   Available to processes               Yes
11 SIGSEGV    Dump        Invalid memory reference             Yes
12 SIGUSR2    Terminate   Available to processes               Yes
13 SIGPIPE    Terminate   Write to pipe with no readers        Yes
14 SIGALRM    Terminate   Real-timer clock                     Yes
15 SIGTERM    Terminate   Process termination                  Yes
16 SIGSTKFLT  Terminate   Coprocessor stack error              No
17 SIGCHLD    Ignore      Child process stopped or terminated  Yes
                          or got a signal if traced 
18 SIGCONT    Continue    Resume execution, if stopped         Yes
19 SIGSTOP    Stop        Stop process execution, Ctrl-Z       Yes
20 SIGTSTP    Stop        Stop process issued from tty         Yes
21 SIGTTIN    Stop        Background process requires input    Yes
22 SIGTTOU    Stop        Background process requires output   Yes
23 SIGURG     Ignore      Urgent condition on socket           No
24 SIGXCPU    Dump        CPU time limit exceeded              No
25 SIGXFSZ    Dump        File size limit exceeded             No
26 SIGVTALRM  Terminate   Virtual timer clock                  No
27 SIGPROF    Terminate   Profile timer clock                  No
28 SIGWINCH   Ignore      Window resizing                      No
29 SIGIO      Terminate   I/O now possible                     No
29 SIGPOLL    Terminate   Equivalent to SIGIO                  No
30 SIGPWR     Terminate   Power supply failure                 No
31 SIGSYS     Dump        Bad system call                      No
31 SIGUNUSED  Dump        Equivalent to SIGSYS                 No


Grau de confiança: 5

### Ex6

O uso de variáveis globais e variáveis estáticas, não é seguro, uma vez que estão disponíveis para qualquer parte do código. O conteúdo existente dentro signal handler, é sensível se assim se pode dizer, e uma vez alterado, poderá alterar totalmente o comportamento do programa, para algo que não é esperado.

Grau de confiança: 4

### Ex7

### a)
 Function               Notes
       abort(3)               Added in POSIX.1-2003
       accept(2)
       access(2)
       aio_error(3)
       aio_return(3)
       aio_suspend(3)         See notes below
       alarm(2)
       bind(2)
       cfgetispeed(3)
       cfgetospeed(3)
       cfsetispeed(3)
       cfsetospeed(3)
       chdir(2)
       chmod(2)
       chown(2)
       clock_gettime(2)
       close(2)
       connect(2)
       creat(2)
       dup(2)
       dup2(2)
       execl(3)               Added in POSIX.1-2008; see notes below
       execle(3)              See notes below
       execv(3)               Added in POSIX.1-2008
       execve(2)

       _exit(2)
       _Exit(2)
       faccessat(2)           Added in POSIX.1-2008
       fchdir(2)              Added in POSIX.1-2013
       fchmod(2)
       fchmodat(2)            Added in POSIX.1-2008
       fchown(2)
       fchownat(2)            Added in POSIX.1-2008
       fcntl(2)
       fdatasync(2)
       fexecve(3)             Added in POSIX.1-2008
       ffs(3)                 Added in POSIX.1-2016
       fork(2)                See notes below
       fstat(2)
       fstatat(2)             Added in POSIX.1-2008
       fsync(2)
       ftruncate(2)
       futimens(3)            Added in POSIX.1-2008
       getegid(2)
       geteuid(2)
       getgid(2)
       getgroups(2)
       getpeername(2)
       getpgrp(2)
       getpid(2)
       getppid(2)
       getsockname(2)
       getsockopt(2)
       getuid(2)
       htonl(3)               Added in POSIX.1-2016
       htons(3)               Added in POSIX.1-2016
       kill(2)
       link(2)
       linkat(2)              Added in POSIX.1-2008
       listen(2)
       longjmp(3)             Added in POSIX.1-2016; see notes below
       lseek(2)
       lstat(2)
       memccpy(3)             Added in POSIX.1-2016
       memchr(3)              Added in POSIX.1-2016
       memcmp(3)              Added in POSIX.1-2016
       memcpy(3)              Added in POSIX.1-2016
       memmove(3)             Added in POSIX.1-2016
       memset(3)              Added in POSIX.1-2016
       mkdir(2)
       mkdirat(2)             Added in POSIX.1-2008
       mkfifo(3)
       mkfifoat(3)            Added in POSIX.1-2008
       mknod(2)               Added in POSIX.1-2008
       mknodat(2)             Added in POSIX.1-2008
       ntohl(3)               Added in POSIX.1-2016
       ntohs(3)               Added in POSIX.1-2016
       open(2)
       openat(2)              Added in POSIX.1-2008
       pause(2)
       pipe(2)
       poll(2)
       posix_trace_event(3)
       pselect(2)
       pthread_kill(3)        Added in POSIX.1-2013
       pthread_self(3)        Added in POSIX.1-2013
       pthread_sigmask(3)     Added in POSIX.1-2013
       raise(3)
       read(2)
       readlink(2)

       readlinkat(2)          Added in POSIX.1-2008
       recv(2)
       recvfrom(2)
       recvmsg(2)
       rename(2)
       renameat(2)            Added in POSIX.1-2008
       rmdir(2)
       select(2)
       sem_post(3)
       send(2)
       sendmsg(2)
       sendto(2)
       setgid(2)
       setpgid(2)
       setsid(2)
       setsockopt(2)
       setuid(2)
       shutdown(2)
       sigaction(2)
       sigaddset(3)
       sigdelset(3)
       sigemptyset(3)
       sigfillset(3)
       sigismember(3)
       siglongjmp(3)          Added in POSIX.1-2016; see notes below
       signal(2)
       sigpause(3)
       sigpending(2)
       sigprocmask(2)
       sigqueue(2)
       sigset(3)
       sigsuspend(2)
       sleep(3)
       sockatmark(3)          Added in POSIX.1-2004
       socket(2)
       socketpair(2)
       stat(2)
       stpcpy(3)              Added in POSIX.1-2016
       stpncpy(3)             Added in POSIX.1-2016
       strcat(3)              Added in POSIX.1-2016
       strchr(3)              Added in POSIX.1-2016
       strcmp(3)              Added in POSIX.1-2016
       strcpy(3)              Added in POSIX.1-2016
       strcspn(3)             Added in POSIX.1-2016
       strlen(3)              Added in POSIX.1-2016
       strncat(3)             Added in POSIX.1-2016
       strncmp(3)             Added in POSIX.1-2016
       strncpy(3)             Added in POSIX.1-2016
       strnlen(3)             Added in POSIX.1-2016
       strpbrk(3)             Added in POSIX.1-2016
       strrchr(3)             Added in POSIX.1-2016
       strspn(3)              Added in POSIX.1-2016
       strstr(3)              Added in POSIX.1-2016
       strtok_r(3)            Added in POSIX.1-2016
       symlink(2)
       symlinkat(2)           Added in POSIX.1-2008
       tcdrain(3)
       tcflow(3)
       tcflush(3)
       tcgetattr(3)
       tcgetpgrp(3)
       tcsendbreak(3)
       tcsetattr(3)
       tcsetpgrp(3)
       time(2)

       timer_getoverrun(2)
       timer_gettime(2)
       timer_settime(2)
       times(2)
       umask(2)
       uname(2)
       unlink(2)
       unlinkat(2)            Added in POSIX.1-2008
       utime(2)
       utimensat(2)           Added in POSIX.1-2008
       utimes(2)              Added in POSIX.1-2008
       wait(2)
       waitpid(2)
       wcpcpy(3)              Added in POSIX.1-2016
       wcpncpy(3)             Added in POSIX.1-2016
       wcscat(3)              Added in POSIX.1-2016
       wcschr(3)              Added in POSIX.1-2016
       wcscmp(3)              Added in POSIX.1-2016
       wcscpy(3)              Added in POSIX.1-2016
       wcscspn(3)             Added in POSIX.1-2016
       wcslen(3)              Added in POSIX.1-2016
       wcsncat(3)             Added in POSIX.1-2016
       wcsncmp(3)             Added in POSIX.1-2016
       wcsncpy(3)             Added in POSIX.1-2016
       wcsnlen(3)             Added in POSIX.1-2016
       wcspbrk(3)             Added in POSIX.1-2016
       wcsrchr(3)             Added in POSIX.1-2016
       wcsspn(3)              Added in POSIX.1-2016
       wcsstr(3)              Added in POSIX.1-2016
       wcstok(3)              Added in POSIX.1-2016
       wmemchr(3)             Added in POSIX.1-2016
       wmemcmp(3)             Added in POSIX.1-2016
       wmemcpy(3)             Added in POSIX.1-2016
       wmemmove(3)            Added in POSIX.1-2016
       wmemset(3)             Added in POSIX.1-2016
       write(2)

Grau de confiança: 3


### b)
Não se deve utilizar printf(), porque este utiliza um buffer, que vai colocando informação em espera para ser impressa, e quando é lhe dada a permissão para imprimir, como por exemplo, uma mudança de linha, só aí ele imprime o que ficou em espera. Sendo assim, caso esta operação seja interrompida, poderá surgir o problema de a informação que está no buffer ser re-escrita, e tudo o que se encontrava lá, é perdido e aquilo que era suposto ser impresso, não o é. Por outro lado, como o write não utiliza um buffer, toda e qualquer informação que é enviada para ser escrita no terminal, será impressa, porque o write não espera por uma permissão para apresentar a informação.

Grau de confiança: 3


### Ex8

Presente no ficheiro pl01b_ex08.c

Para a resolução deste exercício especificamos o comportamento do programa ao receber um SIGUSR1, ao criar um handler para o mesmo, que irá imprimir na consola a informação que capturou o sinal e qual foi o pid do processo que lhe enviou esse sinal. Usamos a função sigaction, para alterar o comportamento do sinal. 

Grau de confiança: 4

### Ex9

Presente no ficheiro pl01b_ex09.c

### a)
Compilando e correndo o exercício 9, e enviando aqueles sinais, através de atalhos do teclado, podemos observar, que o seu funcionamento estava de acordo com o esperado. Conforme o comando, stty -a podemos observar quais são todos os atalhos disponíveis para enviar diretamente os sinais para o programa. 
speed 38400 baud; rows 30; columns 120; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = <undef>; eol2 = <undef>; swtch = <undef>; start = ^Q;
stop = ^S; susp = ^Z; rprnt = ^R; werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
-parenb -parodd -cmspar cs8 -hupcl -cstopb cread -clocal -crtscts
-ignbrk -brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr icrnl ixon -ixoff -iuclc -ixany -imaxbel -iutf8
opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
isig icanon iexten echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke -flusho -extproc

Grau de confiança: 5



### b)
O programa foi interrompido, após o comando CTRL-C. O programa encontrava-se em execução e após o comando CTRL-C o processo recebeu um sinal que interromepeu a sua execução, matando o processo. Recebeu um SIGINT. O seu estado passou a STOPPED.

Grau de confiança: 5



### c)
Presente no ficheiro pl01b_ex09c.c

Como o comando CTRL-C envia um SIGINT para o programa, foi criado um  handler como no exercício 8 para ao receber um sinal SIGINT, imprimir a mensagem  “I won’t let the process end with CTRL-C!”.

Grau de confiança: 4


### d)
O programa foi terminado pelo comando CTRL-/, que enviou um sinal ao processo para ele terminar, recebendo um SIGQUIT. 

Grau de confiança: 4


### e)
Presente no ficheiro pl01b_ex09e.c
Como o comando CTRL-\ envia um SIGQUIT para o programa, foi criado um  handler como no exercício 8 para ao receber um sinal SIGQUIT, imprimir a mensagem  “I won’t let the process end by pressing CTRL-\”.

Grau de confiança: 4


### f)
Como não existe nenhum handler, para o signal SIGINT, quando este sinal é recebido o programa é interrompido, tal como esperado. O seu estado passa para "S", que significa STOPPED.

Grau de confiança: 4

### g)
Como foi criado na alínea um handler para SIGQUIT, o que irá acontecer será o que está dentro do handler, que no caso será a impressão da mensagem "I won’t let the process end by pressing CTRL-\".

Grau de confiança: 4


### h)
Executando o comando "jobs", na consola, acedemos aos processos que ainda estão ativos no sistema, e cada um deles está numerado, começando no 1. Quando executamos o comando "kill %1", matamos o processo presente nos jobs, com o id 1. O %1 representa o processo (job) que queremos atuar.

Grau de confiança: 5


### Ex10

Presente no ficheiro pl01b_ex10.c

### a)

Foi criado um handler que interceta sinais SIGUSR1, e que imprime na consola, que um sinal SIGUSR1 foi recebido e um contador de quantos sinais SIGUSR1 já foram recebidos até ao momento.

Grau de confiança: 4


### b)
Foi criado um handler para SIGUSR1, que ao receber um sinal SIGUSR1, enche a máscara de bloqueio de sinais do programa, para que mais nenhum sinal possa interromper o programa.

Grau de confiança: 3


### c)

Presente no ficheiro pl01b_ex10c.c

Foi adicionado ao código anterior, um fork(), para criar um filho e dentro do filho, um ciclo for que executa 12 vezes o envio de um sinal SIGUSR1, com um intervalo de 10 ms entre cada um, através do uso do usleep e após enviados os 12 sinais, o filho envia para o pai um sinal SIGINT.

Grau de confiança: 4


### d)
Ao adicionar um sleep() de um segundo, consegue-se garantir que o handler consegue interpelar todos os sinais recebidos pelo filho. Sem o uso do sleep, dada a rapidez do sistema operativo, se o sleep não for utilizado, apenas 2 sinais conseguem ser interpelados, porque ao receber os sinais, o programa sabe que os recebeu e são levantadas flags que identificam que foram recebidos sinais, só que como os sinais são recebidos muito rapidamente, apenas 1 flag é atendida, e só 1 sinal é interpelado, ao invés dos 12 recebidos.

Grau de confiança: 3


### e)
Ao limpar a máscara de bloqueio de sinais, permite-se que o programa receba qualquer sinal e que o seu comportamento seja alterado.

Grau de confiança: 4


### Ex11

Presente no ficheiro pl01b_ex11.c
 
 Não, nem todos os sinais, são bloqueados. Existem 3 sinais que nunca podem ser bloqueado, sendo eles o SIGKILL, SIGSTOP e SIGCONT, todos os outros sinais, poderão ser bloqueados, preenchendo a máscara de bloqueio de sinais do programa.

Grau de confiança: 4


### Ex12

Presente no ficheiro pl01b_ex12.c

Para resolver este exercício, é enchida a máscara de bloqueio atráves do fillset(), e são criados 5 filhos atráves da função fork() e de um ciclo for, em que cada um deles percorre 200 posições, que perfazem 1000 posições e imprimem o valor de cada posição. No final de percorrerem 200 posições, cada um dos filhos envia um SIGUSR1 para o pai e mata-se. Enquanto isso o pai encontra-se parado num loop infinito através do uso da função pause(), e vai contando, através de uma variável volatil contador, quantos filhos ainda se encontram em execução. Depois de todos os filhos estarem mortos o pai corre através de um ciclo for a função waitpid(), que recebe a informação da morte dos filhos e o seu status de saída.

Grau de confiança: 3


### Ex13

Presente no ficheiro pl01b_ex13.c

Para a resolução deste problema, criou-se um filho através de um fork(). O pai executa a taskA(), espera 3 segundos e imprime na consola através do printf, a dizer que terminou de executar a tarefa A, e envia ao filho um SIGUSR1 e depois fica à espera da morte do filho, para imprimir a mensagem "The job is complete". Enquanto isso, o filho, executa a tarefa B durante 1 a 5 segundos e quando é terminada imprime com um printf, a informar que a tarefa foi terminada, e quando as tarefas A e B estão completas, o filho executa a tarefa C (taskC()), e envia para a consola a mensagem a informar que a tarefa C foi executada e sai (mata-se).

Grau de confiança: 2


### Ex14


### a) 

Presente no ficheiro pl01b_ex14a.c

Para a resolução deste exercício, foi criado um handler para um sinal SIGALRM, que ao receber um sinal SIGALRM, gerado pela função alarm(), imprime na consola que o utilizador foi demasiado lento ao escrever a sua frase e termina o programa. O utilizador tem apenas 10 segundos para inserir uma string que será lida através de um scanf e o programa calculará o tamanho da string através da função strlen() e imprimirá na consola o tamanho da string inserida pelo o utilizador, terminando posteriormente o programa.


Grau de confiança: 4

### b)

Presente no ficheiro pl01b_ex14b.c

Para a resolução deste problema, reutilizou-se a alínea a), e apenas utilizou-se a função fork() para se criar um filho do processo pai, que irá fazer o controlo do tempo para o utilizador dar input da sua string. Toda a leitura e impressões na consola são feitas pelo pai, e o filho apenas está encarregado de enviar um sigalrm ao pai, caso os 10 segundos passem, esta solução foi conseguida através do uso da função sleep();

Grau de confiança: 4


### Ex15

Para resolver este exercício foi criada uma estrutura de comandos composta por 3 comandos diferentes com diferentes comandos de execução. Foi também criada uma função denominada execute_command que corre cada comando e também um sleep com o tempo de execução de cada comando. Depois foi criado um ciclo for que percorre a estrutura, ou seja, o número de comandos e para cada comando o pai está encarregue de imprimir na consola starting command, enquanto o filho chama a função que executa os comandos e quando o filho termina, dependendo do status de saída do filho, o pai imprime se o comando foi terminado no tempo de execução correto.

Grau de confiança: 1












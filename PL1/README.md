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

O output no terminal serão 2 prints para cada processo. O processo pai irá apresentar o 2º e o 3º print, com x = 0. O processo filho irá apresentar o 1º e o 2º print com x = 2. O pid que o pai recebe do filho é 1234 e o pid do fiho será 0.

Grau de confiança: 5

### b) 

Não, pois não existe nenhum comando wait, ou seja, o processo filho poderá já estar na linha 11 e o processo pai ainda a executar a linha 9. No final, sendo assim, não se garante a ordem dos processos.

Grau de confiança: 5

### Ex2

Presente no ficheiro pl01_ex02.c
Para resolver o exercício 2 foi necessário executar 3 forks, um para cada filho. Foi necessário também incorporar 2 waitpid pois o pai tem de esperar que os filhos executem o seu print para poder fazer também. Na process tree aparece que os filhos não foram terminados, continuam vivos, mas tal não pode acontecer porque se os filhos não forem terminados com exit eles vão executar funções que não deveriam executar.

Grau de confiança: 4

### Ex3

### a) 

Através do seguinte código serão criados 3 processos filho, um em cada fork.

Grau de confiança: 4

### b) 

- ![Alínea b)](SCOMP/pl01_ex03b.png)

Grau de confiança: 5

### c)

A palavra SCOMP é imprimida 8 vezes. 4 vezes pelo processo pai e as restantes vezes pelos processos filho.

Grau de confiança: 5

### Ex4 

### a) 

Apenas a variável a vai ter sempre o mesmo valor. A variável b recebe valores diferentes porque no processo pai toma o valor do pid do filho e no processo filho 0. A variável c no processo pai recebe o seu pid e a mesma coisa para o filho. Em relação á variável d o processo pai recebe o pid do seu pai e o filho recebe o pid do seu pai.

Grau de confiança: 4

### b)

- ![Alínea b)](SCOMP/pl01_ex04b.png)

Grau de confiança: 5

### Ex5

Presente no ficheiro pl01_ex05.c
Para resolver o exercício 5 foi necessário criar 2 filhos, cada um com valores de sleep e exit diferentes. O filho 1 tem valor presente de 1 e o filho 2 tem valor 2 presente em ambos os comandos. No final apenas foi necessário criar 2 waitpid, um cada filho e apresentar um print com exit status de cada um, isto através da função WEXITSTATUS.

Grau de confiança: 4

### Ex6

### a)

- ![Alínea a)](SCOMP/pl01_ex06a.png)

É possível verificar a criação de 8 processos. Como não existe um comando exit, os filhos nunca serão terminados, ou seja, os filhos vão criar filhos e sempre assim até terminar a execução do ciclo for.

Grau de confiança: 2

### b) 

Seria necessário colocar um exit a seguir ao comando sleep, ou seja, cada iteração do ciclo for criava um filho e logo a seguir terminanva-o. Não permitia que esses mesmos criassem descendência.

Grau de confiança: 5

### c) 

De forma, a que o pai espere pelo filhos que tem pid par, é necessário armazenar os pids que apresentam esta caraterística. Para isso foi criado um array de pids. No final o pai irá executar um ciclo for com tamanho do tamanho criado no array. Dentro do ciclo apenas será necessário fazer um waitpid com o pid de i.

Grau de confiança: 2

### d) 

Para a execução do retorno do index dos filhos apenas será necessário retornar o exit com valor de i.

Grau de confiança: 2

### Ex7

Para a resolução do exercício apenas foi necessário fazer um fork e criar um filho. O filho percorria metade do array e atualizava as vezes que a variável n aparece numa variável count1. O mesmo se aplica para o pai com a variável count2 e a restante parte do array.
Para o pai realizar a soma da contagem precisa de saber o valor do filho. A variável do filho encontra-se num processo diferente, processo filho, ou sejam o pai não consegue aceder. Como tal, foi necessário devolver o valor através do exit. Ao executar WEXITSTATUS, o pai ja consegue realizar os cálculos.

Grau de confiança: 3

### Ex8

### a)

Não, o segundo filho não aparece na lista de processos. Ambos os filhos foram terminados com exit. O primeiro filho aparece mas está defunto, ainda não foi limpo da lista de processos.

Grau de confiança: 2

### b) 

Ambos os filhos foram terminados mas apenas um deles aparece no terminal. Aparece mas num estando defunto. Se levarmos para a linguagem popular para um melhor entendimento por detrás do processo, "ainda não foi realizado o seu funeral".

Grau de confiança: 3

### c) 

Ao executar o comando kill e matar o processo pai, ambos os seus processos descendentes serão eliminados também.

Grau de confiança: 4

### Ex9

### a)

Não, o output não estará de forma ordenada pois não há garantia que o segundo filho será executado antes do terceiro (e.g). Seria possível garantir a sua ordenação mas seria através do uso da função waitpid.
Para a resolução do exercício apenas foi necessário invocar a função fork dentro de um ciclo for. Apenas o filho imprime os seus numeros baseando-se no seu index. Após finalizar a sua função o mesmo irá ser terminado através de um exit pois caso não acontecesse o mesmo iria criar descendência.

Grau de confiança: 3

### Ex10

Para a escrita do programa, foi adicionado ao excerto de código já presente um array de pids e um array de aparências. Cada filho presente no array terá de fazer o mesmo excerto mas com indexs diferentes. Caso se encontre correspondência com a variável n o resultado será devolvido através do função com a posição relativa como valor de retorno e 255 (número fora da range de cada filho) caso não seja encontrado. Após todos os filhos terem realizado as suas tarefas, o processo pai apenas terá de reunir os dados e colocá-los num array denominado appear. O único acesso que o mesmo tem com os filhos é através da função exit. Através do WEXITSTATUS consegue os valores das posições relativas dos filhos e colocar no array para posteriormente ser executado o print.

Grau de confiança: 3

### Ex11

### a) 

Na primeira alínea é pedido a criação de 5 processos filho que executem ao mesmo tempo e que devolvam o valor máximo presente em 1/5 do array posteriormente criado. Basta criar um array de pids e executar fork dentro de um ciclo for para a criação dos mesmos. Ambos vão procurar  o valor máximo e armazenar o valor numa variável denominada max_value sendo esta retornada através da função exit.

Grau de confiança: 3

### b)

Apenas foi necessário o pai ter acesso ao valor de max_value através do WEXITSTATUS e criar um segundo filho através do fork. O filho apenas terá de executar o cálculo em metade do array e imprimir os resultados.

Grau de confiança: 2

### c)

Igual à alínea anterior apenas com a diferença de ser o processo pai a realizar os cálculos e na metade restante do array.

Grau de confiança: 4

### d)

Para o output do exercício ser ordenado pelos index apenas foi necessário colocar um waitpid no processo pai, o que irá resultar na espera do termino do processo filho.

Grau de confiança: 4

### Ex12

### a)

Para a execução do exercício apenas foi necessário criar a função spawn_childs que retorna o valor do index dos filhos e 0 para o processo pai. Apenas foi criado um ciclo for com um fork presente e um return do index (Não é possível usar exit pois o mesmo é executado quando queremos terminar a execução de algo, neste caso apenas queremos retornar um valor para a função main), sendo o mesmo imprimido posteriormente na função main. Foi acrescentado um sleep de 1 segundo no pai para o mesmo dar tempo ao último filho de executar o seu print.

Grau de confiança: 4

### b)

A execução é a mesma da alínea anterior mas apenas com 6 processos filhos, ao contrário do anterior que permitia a criação de n. A única diferença é que agora o processo pai necessita de ter um wait para esperar que os processos filho sejam retornados.

Grau de confiança: 4



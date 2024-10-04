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

## PL2 ##

### Ex1

Para resolver o exercício 1 foi necessário criar um pipe denominado fd, pipe esse que será utilizado na comunicação entre o processo pai e o processo filho. Foi executado o comando fork para criar o processo filho e no seu código respetivo começamos por fechar o descritor de leitura, escrevemos uma mensagem com o pid do filho e fechamos o descritor que estava aberto, o de escrita. De seguida, o processo pai apenas começa por fechar o descritor de escrita pois não o irá usar, lê a mesnagem com o pid do filho e imprime, terminando com o close do descritor de leitura.

Grau de confiança: 5

### Ex2

### a) 

Começamos por declarar as variáveis, criar o processo filho e este será responsável pela leitura dos inputs. Logo a seguida, este mesmo irá enviar estes dados para o processo pai mas através de 2 writes diferentes, um para cada variável. O processo pai apenas lê as variáveis e com 2 reads, um para o int e outro para a string. Apenas terá que os imprimir logo após a leitura.

Grau de confiança: 5

### b) 

A alínea b) é muito semelhante à alínea anterior apenas com a exceção do número de leituras e escritas. Apenas será efetuada 1 pois ambos os inputs se encontram dentro da struct definida.

Grau de confiança: 5

### Ex3 

O processo pai começa por enviar uma estrutura com 2 strings e fecha o seu descritor de escrita. O filho lê as mensagens e imprime-as. Após a sua impressão termina. O processo pai espera pelo seu filho através do waitpid e recebe o valor de saída do filho através do WEXITSTATUS e imprime juntamente com o pid do filho.

Grau de confiança: 5

### Ex4

O processo pai começa por abrir o ficheiro usando a função fopen. Obtém os valores presentes nas linhas através da função fgets e escreve no pipe usando enquanto não encontra uma linha a null. O processo filho apenas lê os valores presentes e da imprime. O processo filho lê enquanto o retorno da função read não é 0, ou seja, enquanto tem algo para ler no pipe partilhado com o pai.

Grau de confiança: 3

### Ex5  

Para resolver o exercício 5 foram necessários 2 pipes. O processo filho começa por ler uma string do teclado e envia a frase para o processo pai. O processo pai averigua se a primeira letra da frase é maiúscula ou minúscula. Converte a frase para o seu contrário, isto é, se for minúscula converte para maiúscula ou vice-versa. Envia para o filho e este apenas imprime a frase resultante.

Grau de confiança: 4

### Ex6

No início são criados 2 arrays de inteiros que foram preenchidos com valores random. Serão criados 5 processos filhos, cada um responsável por 1/5 dos arrays. Cada filho efetua os cálculos e coloca numa variável temporária que posteriormente irá ser inserida na estrutura na posição correta.O processo pai espera pelo término dos filhos, apenas lê os valores e soma-os, colocando-os numa variável valor total. Posteriormente o processo pai imprime o valor.
Não é necessário um mecanismo de sincronização pois cada filho está apenas respon´savel por uma parte do array. Existe também o fator do pipe ser bloqueante.

Grau de confiança: 4

### Ex7

Este exercício é igual ao exercício anterior mas apenas tem uma diferença, existe um pipe para cada filho.

Grau de confiança: 4

### Ex8 

Para a resolução do exercício 8 foi utilizado apenas um pipe que estabelece a conexão entre pai e filho. O pai escreve a cada 2 segundos (utiliza um sleep) numa estrutura com uma mensagem e com um int que corresponde ao número da ronda. O pai envia esses valores para o filho que posteriormente irá imprimir a mensagem e enviar através do seu valor de saída o número da ronda. No final, o pai apenas terá que esperar que os filhos terminem, usando um waitpid e WEXITSTATUS para recuperar o valor de saída do filho. 

Grau de confiança: 3

### Ex9 

Para resolver o exercício foi necessário declarar uma estrutura com 3 int. Já no main foi criado um array de estruturas e preenchido de forma aleatória. Foram criados 10 filhos e cada um responsável por 1/10 do array de sales e caso encontrasse um produto com quantidade superior a 20, enviava para o processo pai através de um pipe. O processo pai executava enquanto tinha algo para ler no pipe e adicionava num array de produtos para posteriormente ser imprimido.

Grau de confiança: 4

### Ex10 

o processo pai começa por enviar um valor aleatório, compreendido entre 1 e 5, para o processo filho e um valor que indica se o filho poderá efetuar uma nova aposta. o filho irá ler esses valores e se o valor for 0 termina, ou seja, o seu crédito terminou. Se o valor for 1 irá ser efetuada uma verificação da aposta do filho. O processo filho irá gerar um valor aleatório e enviar para o pai. O pai, posteriormente, averigua se o valor é o mesmo. Caso não seja, decrementa o valor do crédito e vice-versa. Este processo é executado enquanto o crédito do filho é diferente de 0.

Grau de confiança: 3

### Ex11

Começamos por criar um array de pipes e um array de pids. O processo pai gera um valor aleatório e envia para o processo filho. O processo filho analisa e compara o seu valor com o valor do pai. Após averiguar, envia para o filho seguinte o maior valor. Após todos os filhos terem terminado a comparação, o processo pai imprime o maior valor.

Grau de confiança: 2

### Ex12

Para a resolução do exercício 12 foi necessário criar 2 pipes e um array de produtos. Começamos por preencher o array de produtos com valores de aleatórios. Cada processo filho começa por enviar um código aleatório para o processo pai e o processo pai verifica na sua "base de dados" o produto e envia, através de outro pipe, o nome e o preço do produto, valores esses que o filho (barcode reader) irá imprimir.

Grau de confiança: 2

### Ex13 




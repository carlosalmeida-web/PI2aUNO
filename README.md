# UNO Projeto Integrador 2

## Introdução

O projeto visa desenvolver um jogo de cartas chamado UNO para ser jogado em console, seguindo as mesmas regras do jogo original. O desenvolvimento do jogo utilizará listas simplesmente ligadas, listas duplamente ligadas, estruturas e outros conceitos abordados no curso de Estrutura de Dados.

## Requisitos do Projeto

## Funções
### Função: CriarBaralho
A função `CriarBaralho` cria uma estrutura de Baralho vazia e verifica se o Baralho está vazio. Se o Baralho estiver vazio, a função retorna a estrutura do Baralho criada.

### Função: baralhoVazio
A função `baralhoVazio` verifica se o baralho passado como parâmetro está vazio. A função retorna 1 se o baralho estiver vazio e 0 se não estiver vazio.

### Função: baralhoCheio
A função `baralhoCheio` recebe como parâmetro um baralho que é verificado se está vazio, retornando o número 1 se estiver vazio e 0 se não estiver vazio.

### Função: AdicionarCarta
A função `AdicionarCarta` recebe como parâmetro um Baralho e uma Carta. A função verifica se o baralho está cheio, caso esteja, ele retorna um texto de baralho cheio, caso contrario, a Carta do parâmetro é adicionada ao baralho.

### Função: pegarCarta
A função `pegarCarta` recebe como parâmetro o baralho de compra e verifica se está vazio, se estiver retorna uma carta vazia, caso contrario, a carta retornada é a do topo do baralho.

### Função: checarLista
A função `checarLista` verifica e imprime as cartas presentes na lista de manilhas (cartas) do jogador atual no jogo de UNO. A função itera através da lista duas vezes: a primeira vez no sentido horário (próximo) e a segunda vez no sentido anti-horário (anterior). Durante a iteração, ela imprime a categoria e o número de cada carta.

### Função: listarBaralho
A função `listarBaralho` percorre e imprime todas as cartas presentes em um baralho. Para cada carta, a função imprime o número e a categoria.

### Função: listarManilha
A função `listarManilha` imprime na saída padrão as informações das cartas presentes na lista de manilhas de uma estrutura `Manilha`. Essa função é utilizada para visualizar as cartas jogadas durante o jogo, mostrando seus números e categorias.

### Função: criarManilha
A função `criarManilha` aloca dinamicamente memória para uma nova estrutura `Manilha`, inicializa seus campos e retorna um ponteiro para ela. Esta função é usada para criar e inicializar uma nova estrutura `Manilha` antes de ser utilizada no jogo.

### Função: slotOrdemManilha
A função `slotOrdemManilha` retorna o ponteiro para o primeiro nó da lista de manilhas de uma cor específica na estrutura `Manilha`. Essa função é utilizada para acessar a lista de manilhas correspondente à cor especificada durante o jogo.

### Função: adicionarManilhaAtualSlotCor
A função `adicionarManilhaAtualSlotCor` adiciona a carta atualmente em jogo à lista de manilhas de uma cor específica na estrutura `Manilha`. Esta função é usada durante o jogo para atribuir a carta atual à lista de manilhas correspondente à sua cor.


### Função: slotCorVazio
A função `slotCorVazio` verifica se a lista de manilhas de uma cor específica na estrutura `Manilha` está vazia. As manilhas representam as cartas jogadas de uma determinada cor durante o jogo. Esta função é útil para determinar se não há cartas de uma cor específica jogadas no momento.

### Função: adicionarNoManilha
A função `adicionarNoManilha` é responsável por adicionar uma nova carta à lista de manilhas de uma cor específica na estrutura `Manilha`. Essa função realiza várias operações, incluindo alocação de memória para um novo nó de manilha, inserção da carta nesse nó, incremento da contagem de cartas na estrutura `Manilha` e, dependendo do caso, inserção ordenada da nova carta na lista de manilhas.

### Função: getBaralhoCompra
A função `getBaralhoCompra` retorna o ponteiro para o baralho de compra associado ao jogo especificado na estrutura `Jogo`.
Linha 474

## Estruturas

## Carta

### A estrutura da Carta é composta por duas variáveis, uma guarda o número da carta e a segunda guarda a cor.
```C
typedef struct carta {
    
    enum numero 
    {
        ZERO,
        UM,
        DOIS,
        TRES,
        QUATRO,
        CINCO,
        SEIS,
        SETE,
        OITO,
        NOVE,
        MAIS2,
        INVERTER,
        PULAR,
        CURINGA,
        MAIS4
    } numero;

    char categoria;

} Carta;
```
### A categoria guarda a cor em um único carácter, sendo:
* R representa uma carta vermelha.
* B representa uma carta azul.
* y representa uma carta amarela.
* G representa uma carta verde.
* J representa uma carta coringa.
###### Coringa é uma carta que pode ser jogada independente de cor ou número no topo do Baralho da mesa.

## 
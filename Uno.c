#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
# define getName(var, str)  sprintf(str, "%s", #var) 

#include "Uno.h"
//#define getName(var, str)  sprintf(str, "%s", #var)

//#define BARALHO_SIZE 108



typedef struct carta {
    
    enum numero {
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
        MAIS2, // compra 2
        INVERTER,
        PULAR,
        CORINGA, // troca de cor
        MAIS4 // compra 4
    } numero;

    char categoria;

} Carta;

// Coloque: tipoCarta[carta.numero] para retornar o tipo da carta solicitada.
static const char * const tipoCarta[] = {
	[ZERO] = "0",
	[UM] = "1",
	[DOIS] = "2",
	[TRES] = "3",
    [QUATRO] = "4",
    [CINCO] = "5",
    [SEIS] = "6",
    [SETE] = "7",
    [OITO] = "8",
    [NOVE] = "9",
    [MAIS2] = "+2",
    [INVERTER] = "Inverter",
    [PULAR] = "Pular",
    [CORINGA] = "Coringa",
    [MAIS4] = "+4",
};

typedef struct manilha
{
    
    unsigned int *qtd;
    Carta carta;
    struct manilha *ant, *prox;

}Manilha;

typedef struct perfil{
    char nome[15];
    unsigned int wins;
}Perfil;

typedef struct ciclo{
    
    Perfil *perfil;
    Manilha *mAtual;
    struct ciclo *ant, *prox;

}Ciclo;
//Descritor de Ciclo
typedef struct jogo{
    
    int qtdJogadas;
    int qtdJogadores;
    bool isInverso;
    Baralho *bMesa;
    Ciclo *cAtual;

}Jogo;

typedef struct baralho {
    Carta carta[BARALHO_SIZE];
    int topo;
} Baralho;

// Função para inicializar o baralho
Baralho *criarBaralho(){
    Baralho *mesa = (Baralho*)malloc(sizeof(Baralho));

    if(mesa == NULL){
        printf("Erro: falha ao alocar memória para o baralho!\n");
        return NULL;
    }    
    
    mesa->topo = -1;

    return mesa;
}

// Função para verificar se o baralho está vazio
int baralhoVazio(Baralho *baralho) {
    return (baralho->topo == -1); // Retorna 1 se estiver vazio, 0 caso contrário
}

// Função para verificar se o baralho está cheio
int baralhoCheio(Baralho *baralho) {
    return (baralho->topo == BARALHO_SIZE - 1); // Retorna 1 se estiver cheio, 0 caso contrário
}

// Função para adicionar uma carta ao baralho
void adicionarCarta(Baralho *baralho, Carta carta) {
    if (baralhoCheio(baralho)) {
        printf("Erro: o baralho está cheio\n");
    } else {
        baralho->topo++; // Incrementa o topo
        baralho->carta[baralho->topo] = carta; // Adiciona a carta à posição do topo
    }
}

// Função para remover uma carta do baralho
Carta pegarCarta(Baralho *baralho) {

    if (baralhoVazio(baralho)) {
        printf("Erro: o baralho está vazio\n");
        Carta cartaVazia = {-1, ""}; // Carta vazia para indicar erro
        return cartaVazia; // Retorna uma carta vazia indicando erro
    }

    Carta carta = baralho->carta[baralho->topo]; // Obtém a carta do topo
    baralho->topo--; // Decrementa o topo
    return carta; // Retorna a carta removida
    
}

void listarBaralho(Baralho *cartas){
    
    for(int i = 0; i <= cartas->topo; i++)
        printf("Número: %d, Categoria: %c\n", cartas->carta[i].numero, cartas->carta[i].categoria);
    
}

void listarManilha(Manilha *cartas) {
    //Manilha *carta = (Manilha*)malloc(sizeof(Manilha));
    Manilha *carta = cartas;
    do{
        printf("Número: %s, Categoria: %c\n", tipoCarta[cartas->carta.numero], cartas->carta.categoria);
        printf("quantidade: %d\n", *(cartas->qtd));
        cartas = cartas->prox;
    }while (cartas != NULL && cartas != carta);
}

Manilha *inicializarManilha() {
    Manilha *manilha = (Manilha*)malloc(sizeof(Manilha));
    manilha->qtd = (unsigned int*)malloc(sizeof(unsigned int));
    *(manilha->qtd) = 0;
    manilha->prox = NULL;
    manilha->ant = NULL;

    return manilha;
}

Jogo *criarJogo(Ciclo *ciclo){
        Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
        if(jogo == NULL){ 
            printf("Erro: falha ao alocar memória para o Descritor Jogo.\n");
            return NULL;
        }
        jogo->bMesa = (Baralho *)malloc(sizeof(Baralho));
        jogo->qtdJogadas = 0;
        jogo->qtdJogadores = 0;
        jogo->cAtual = ciclo;
        jogo->isInverso = false;
    
    return jogo;
}

void proximoCiclo(Jogo *jogo){
    if(jogo == NULL || jogo->cAtual == NULL){
        printf("Erro: jogo ou ciclo atual são inválidos!");
        return;
    }
    if(jogo->isInverso == false){
    jogo->cAtual = jogo->cAtual->prox;
    printf("mem: %p\n",jogo->cAtual);
    }else{
    jogo->cAtual = jogo->cAtual->ant;
    printf("mem: %p\n",jogo->cAtual);
    }

}

bool isPlayer(Jogo *jogo){
    return jogo->cAtual->perfil->nome != NULL;
}

void distribuirBaralho(Baralho *baralho, Manilha **manilha, int quant) {
    if (baralhoVazio(baralho)) {

        printf("\nErro: Baralho Vazio, não foi possível transferir %d Cartas para a manilha\n", quant);
        return;

    }

    for (;quant > 0; quant--) {

        Carta carta = baralho->carta[baralho->topo];
        baralho->topo--;

        Manilha *novoNo = (Manilha*)malloc(sizeof(Manilha));
        novoNo->qtd = (*manilha)->qtd; // Usa o mesmo ponteiro qtd da manilha

        if ((*manilha)->prox == NULL){
            
            novoNo->ant = novoNo;
            novoNo->prox = novoNo;
            *manilha = novoNo;

        } else {

            novoNo->ant = (*manilha)->ant;
            novoNo->prox = *manilha;
            (*manilha)->ant->prox = novoNo;
            (*manilha)->ant = novoNo;

        }

        novoNo->carta = carta;
        (*(novoNo->qtd))++; // Incrementa a quantidade de cartas na manilha
    }
}

void listarCiclo(Ciclo *ciclo){
    Ciclo *tempCiclo = ciclo;
    if(ciclo == NULL) return;
    do{
        printf("Memoria: %p\n", *ciclo);

        ciclo = ciclo->prox;
    }while (ciclo != NULL && ciclo != tempCiclo);
}

void adicionarCiclo(Jogo *jogo, Manilha *manilha, bool _isPlayer) {
    if (jogo == NULL || manilha == NULL) {
        printf("Erro: Jogo ou Manilha não inicializados!\n");
        return;
    }

    if (jogo->cAtual == NULL) {
        printf("Erro: Ciclo não inicializado, falha ao adicionar Manilha ao Ciclo de jogo!\n");
        return;
    }

    Ciclo *novoNo = (Ciclo *)malloc(sizeof(Ciclo));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para novoNo em adicionar Ciclo!\n");
        return;
    }

    if(_isPlayer) {
        novoNo->perfil = malloc(strlen("player") + 1);
        strcpy(novoNo->perfil->nome, "player"); 
        }else{
        novoNo->perfil = malloc(strlen("\0"));
        novoNo->perfil = '\0';
    }
    novoNo->mAtual = manilha;
    novoNo->ant = jogo->cAtual->ant;
    novoNo->prox = jogo->cAtual;

    jogo->cAtual->ant->prox = novoNo;
    jogo->cAtual->ant = novoNo;

    jogo->qtdJogadores++;
}

Ciclo *criarCiclo(){
    Ciclo *ciclo = (Ciclo *)malloc(sizeof(Ciclo));
    if(ciclo == NULL){
        printf("Erro: Falha ao alocar memoria para o ciclo de jogo!\n");
        return NULL;
    } 

    ciclo->prox = ciclo;
    ciclo->ant = ciclo;
    ciclo->perfil = NULL;

    return ciclo;
}

void embaralharMatriz(char matrix[2][BARALHO_SIZE]) {
    srand(time(NULL));

    for (int i = BARALHO_SIZE-1; i > 0; i--) {
        int j = rand() % (i + 1);

        int temp = matrix[0][i];
        matrix[0][i] = matrix[0][j];
        matrix[0][j] = temp;

        temp = matrix[1][i];
        matrix[1][i] = matrix[1][j];
        matrix[1][j] = temp;
    }

}

Baralho* gerarBaralho() {
    printf("teste\n");
    FILE *arquivo;
    arquivo = fopen("baralho.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }
    printf("teste\n");

    char cartas[2][BARALHO_SIZE];
    char linha[10];  
    int contador = 0;    
    printf("teste\n");
    

    arquivo = fopen("baralho.txt", "r");
    if (arquivo == NULL) {
        printf("Erro Crítico: falha ao abrir o arquivo.");
        exit(1);
    }

    // Ler as cartas do arquivo e armazenar na matriz
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha, "%c - %d", &cartas[0][contador], &cartas[1][contador]) == 2) {
        printf("Carta lida: %c - %d\n", cartas[0][contador], cartas[1][contador]);
        contador++;
    }
    }

    printf("teste\n");

    fclose(arquivo);

    embaralharMatriz(cartas);

    Baralho* baralho_principal = (Baralho*)malloc(sizeof(Baralho));
    if (baralho_principal == NULL) {
        printf("Erro: ao alocar memória para o baralho!\n");
        return NULL;
    }

    baralho_principal->topo = -1;
    for (int i = 0; i < BARALHO_SIZE; i++) {
        baralho_principal->topo++;
        baralho_principal->carta[baralho_principal->topo].categoria = cartas[0][i];
        baralho_principal->carta[baralho_principal->topo].numero = cartas[1][i];
    }
    
    for (int i = 0; i <= baralho_principal->topo; i++) {
        printf("Carta %d:\n", i + 1);
        printf("Categoria: %c\n", baralho_principal->carta[i].categoria);
        printf("Número: %d\n\n", baralho_principal->carta[i].numero);
    }

    system("pause");

    return baralho_principal;
}

void reembaralhar(Baralho *baralho, Baralho *mesa){
    Carta topo_mesa = pegarCarta(mesa);
    int tamanho_vetor = mesa->topo + 1;
    Carta vetor[tamanho_vetor];
    int i = 0;
    while(!baralhoVazio(mesa)){
        vetor[i] = pegarCarta(mesa);
        i++;
    }
    Carta temp;
    for(int i = 0, j = (tamanho_vetor-1); i <= j; i++, j--){
        int random_num = rand() % (tamanho_vetor-1);
        
        temp.categoria = vetor[i].categoria;
        temp.numero = vetor[i].numero;

        vetor[i].categoria = vetor[random_num].categoria;
        vetor[i].numero = vetor[random_num].numero;
        
        vetor[random_num].categoria = temp.categoria;
        vetor[random_num].numero = temp.numero;

        random_num = rand() % (tamanho_vetor-1);
        
        temp.categoria = vetor[j].categoria;
        temp.numero = vetor[j].numero;
        
        vetor[j].categoria = vetor[random_num].categoria;
        vetor[j].numero = vetor[random_num].numero;
        
        vetor[random_num].categoria = temp.categoria;
        vetor[random_num].numero = temp.numero;
    
    }
    for(int i = 0; i < tamanho_vetor; i++){
        adicionarCarta(baralho, vetor[i]);
    }
    adicionarCarta(mesa, topo_mesa);
}

Carta *topoBaralho(Baralho *baralho) {
  if (baralho == NULL) {
    printf("Erro: baralho não inicializado\n");
    Carta cartaVazia = {-1,""};
    exit(1);
  }
  return &(baralho->carta[baralho->topo]);
}

bool jogadaValida(Carta *pCarta, Carta *mCarta) {
    if(pCarta == NULL){
        perror("Erro: pCarta não inicializada!\n");
    }
    if(mCarta == NULL){
        perror("Erro: mCarta não inicializada!\n");
    }
    printf("jogadaValida\n");
  if (pCarta->categoria == mCarta->categoria || 
      pCarta->categoria == 'J' ||
      pCarta->numero == mCarta->numero){
              printf("jogadaValida saiuda\n");

    return true;
      }
        printf("jogadaValida saiuda\n");

  return false;
}

bool selecionarCarta(char tecla, Jogo *jogo) {
  switch (tecla) {
  case 'A':
    jogo->cAtual->mAtual = jogo->cAtual->mAtual->ant;
    return false;
    break;
  case 'D':
    jogo->cAtual->mAtual = jogo->cAtual->mAtual->prox;
    return false;
    break;
  case 'W':
    /*if (jogadaValida(&(jogo->cAtual->mAtual->carta),
                     &(jogo->bMesa->carta[jogo->bMesa->topo]))) {
      Manilha *mTemp = jogo->cAtual->mAtual;
      jogo->cAtual->ant->prox = mTemp->prox;
      // terminar lógica
      adicionarCarta(jogo->bMesa, jogo->cAtual->mAtual->carta);
      return true;
    }*/
    printf("Jogada Inválida");
    return false;

    break;
  case 'S':

    break;
  }
  return false;
}

// vetor de cartas jogaveis
/*int **CartasJogaveis(Carta *topo, Manilha *cartas){
    Manilha *atual = cartas;
    int ** jogaveis;
    int num_jogaveis=0;
    do{
        if(topo->categoria  == atual->carta.categoria|| atual->carta.numero == topo->numero || atual->carta.categoria == "J"){
            num_jogaveis++;
            jogaveis = realloc(jogaveis, sizeof(int *) * num_jogaveis);
            jogaveis[num_jogaveis - 1] = atual;
    }

    atual=atual->prox;
  } while (atual != cartas);
  return jogaveis;   
}*/

void **cartasJogaveis(Carta *topo, Manilha *atual){
    void **ptrs = malloc(sizeof(void *));
    if (!ptrs) {
        perror("Erro ao alocar memória\n");
        exit(1);
    }
  
    int *quant = malloc(sizeof(int));
    if (!quant) {
        perror("Erro ao alocar memória\n");
        exit(1);
    }

    *quant = 0;
    Manilha *tempMani = atual;

    do{

        if(atual == NULL){
            perror("Erro: manilha não alocada!\n");
            exit(1);
        }

      if(jogadaValida(&(atual->carta), topo)){

        (*quant)++;
        ptrs = realloc(ptrs, sizeof(void *) * ((*quant)+1));
        ptrs[*quant] = atual;

      }

      atual = atual->prox;
    }while(atual != tempMani);
    ptrs[0] = quant;

    return ptrs;
}

void printCarta(Manilha *manilha) {
    if(manilha == NULL) {
        perror("Erro: Carta vazia!\n");
        return;
    }
    printf("Carta:\ncategoria: %c\n", manilha->carta.categoria);
    printf("numero: %d\n\n", manilha->carta.numero);

}

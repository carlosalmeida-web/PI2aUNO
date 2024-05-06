#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
# define getName(var, str)  sprintf(str, "%s", #var) 

#include "Uno.h"
//#define getName(var, str)  sprintf(str, "%s", #var)

//#define BARALHO_SIZE 108

/*NoManilha { Carta *carta, Manilha ListaJogadorCircular;}

Manilha { unsigned int qtd, NoManilha *início, NoManilha *inicioAzul, NoManilha *inicioVermelho, NoManilha *inicioVerde, NoManilha *inicioAmarelo, NoManilha *inicioCoringa }

NoJogador{ char nome[15],  unsigned int wins, Manilha() }

listaJogadorCircular{ int qtdJogadores, int qtdJogadas , NoJogador *inicio, bool isInverso}

Jogo { Baralho *BMesa, Baralho *BCompra, listaJogadorCircular *lista }

distribuirBaralho() -> se adequar às mudanças do código.

reembaralhar() -> resetarBaralho()

resetarBaralho(): Adicionar checagem para carta coringa de troca de cor (vira cor curinga).

NoJogador passa a ser Manilha()
*/

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
        MAIS2, // compra 2
        INVERTER,
        PULAR,
        CURINGA, // troca de cor
        MAIS4 // compra 4
    } numero;

    char categoria;

} Carta;

// Coloque: tipoCarta[carta.numero] para retornar o tipo da carta solicitada.
static const char * const tipoCarta[] = 
{
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
    [CURINGA] = "Curinga",
    [MAIS4] = "+4",
};

typedef struct noManilha
{
    
    Carta carta;
    struct noManilha *ant, *prox;

}NoManilha;

typedef struct manilha
{
    
    unsigned int qtd;
    NoManilha *mAtual;
    
    struct noManilha *inicioAzul;
    struct noManilha *inicioVermelho;
    struct noManilha *inicioVerde;
    struct noManilha *inicioAmarelo;

    
    
    struct noManilha *inicioCuringa;

} Manilha;

typedef struct perfil
{
    
    char nome[15];
    unsigned int wins;
    
}Perfil;

typedef struct settings{
    
    char ordem[5];
    
}Settings;

typedef struct noJogador
{    

    Manilha *manilha;
    Perfil *perfil;
    bool isBot;
    struct noJogador *ant, *prox;

} NoJogador;

typedef struct listaJogadorCircular
{

    NoJogador *jAtual;
    int qtdJogadores;
    int qtdJogadas;
    bool isInverso;

}ListaJogadorCircular;

typedef struct baralho {
    
    Carta cartas[BARALHO_SIZE];
    int topo;

} Baralho;

typedef struct jogo
{
    
    Baralho *bMesa;
    Baralho *bCompra;
    ListaJogadorCircular *cicloJogadores;

}Jogo;

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
        baralho->cartas[baralho->topo] = carta; // Adiciona a carta à posição do topo
    }
}

// Função para remover uma carta do baralho
Carta pegarCarta(Baralho *baralho) {

    if (baralhoVazio(baralho)) {
        printf("Erro: o baralho está vazio\n");
        Carta cartaVazia = {-1, ""}; // Carta vazia para indicar erro
        return cartaVazia; // Retorna uma carta vazia indicando erro
    }

    Carta carta = baralho->cartas[baralho->topo]; // Obtém a carta do topo
    baralho->topo--; // Decrementa o topo
    return carta; // Retorna a carta removida
    
}

void listarBaralho(Baralho *cartas){
    
    for(int i = 0; i <= cartas->topo; i++)
        printf("Número: %d, Categoria: %c\n", cartas->cartas[i].numero, cartas->cartas[i].categoria);
    
}

void listarManilha(Manilha *cartas) {
    //Manilha *carta = (Manilha*)malloc(sizeof(Manilha));
    Manilha *carta = cartas;
    do{
        printf("Número: %s, Categoria: %c\n", tipoCarta[cartas->mAtual->carta.numero], cartas->mAtual->carta.categoria);
        printf("quantidade: %d\n",cartas->qtd);
        cartas = cartas->mAtual->prox;
    }while (cartas != NULL && cartas != carta);
}

Manilha *criarManilha() {
    Manilha *manilha = (Manilha*)malloc(sizeof(Manilha));
    manilha->qtd = (unsigned int*)malloc(sizeof(unsigned int));
    manilha->mAtual = NULL;

    manilha->inicioVermelho = NULL;
    manilha->inicioVerde = NULL;
    manilha->inicioAmarelo = NULL;
    manilha->inicioAzul = NULL;
    manilha->inicioCuringa = NULL;

    return manilha;
}

NoManilha *slotOrdemManilha(Manilha *manilha, char cor, bool reservar) {
    switch(cor)
    {
        case 'R':
            if(reservar && !manilha->inicioVermelho)
                manilha->inicioVermelho = malloc(sizeof(NoManilha));
            return manilha->inicioVermelho;
        case 'G':
            if(reservar && !manilha->inicioVerde)
                manilha->inicioVerde = malloc(sizeof(NoManilha));
            return manilha->inicioVerde;
        case 'B':
            if(reservar && !manilha->inicioAzul)
                manilha->inicioAzul = malloc(sizeof(NoManilha));
            return manilha->inicioAzul;
        case 'Y':
            if(reservar && !manilha->inicioAmarelo)
                manilha->inicioAmarelo = malloc(sizeof(NoManilha));
            return manilha->inicioAmarelo;
        case 'C':
            if(reservar && !manilha->inicioCuringa)
                manilha->inicioCuringa = malloc(sizeof(NoManilha));
            return manilha->inicioCuringa;
    }
}

void adicionarNoMalinha(Manilha *manilha, Carta *carta) {
    
    char cor[5] = "RGBYC";
    if(!manilha || !carta)
    {
        perror("Erro: Manilha não alocada!");
        exit(1);
    }
    NoManilha *noManilha = (NoManilha*)malloc(sizeof(NoManilha));
    if(!noManilha)
    {
        perror("Erro: Falha ao alocar no Manilha!");
        exit(1);
    }

    noManilha->carta = *carta;
    manilha->qtd++;

    NoManilha *corAtual = slotOrdemManilha(manilha, carta->categoria, true);
    NoManilha *tempManilha;

    if(!&corAtual->carta)
    {
        corAtual->carta = *carta;
        char *posicao = strchr(cor, carta->categoria);
        int indice = posicao - cor;
        for(int i = 1;; i++)
        {
            if(!cor[indice + i])
            {
                indice = 0;
                i = 0;
            }
            tempManilha = slotOrdemManilha(manilha, cor[indice + i], false);
            if(tempManilha)
            {

                tempManilha->ant->prox = noManilha;
                noManilha->ant = tempManilha->ant;
                tempManilha->ant = noManilha;
                noManilha->prox = tempManilha;
                continue;

            }

        }
    }
    else
    {
        tempManilha = corAtual;
        for(;;){
            tempManilha = tempManilha->prox;
            if(
            tempManilha->carta.categoria != carta->categoria || 
            tempManilha->carta.numero > carta->numero ||
            tempManilha == corAtual 
            )
            {
            
                tempManilha->ant->prox = noManilha;
                noManilha->ant = tempManilha->ant;
                tempManilha->ant = noManilha;
                noManilha->prox = tempManilha;
                continue;

            }
    }
    }
}

Jogo *criarJogo(NoJogador *noJogador){
        Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
        if(jogo == NULL){ 
            printf("Erro: falha ao alocar memória para o Descritor Jogo.\n");
            return NULL;
        }
        jogo->bMesa = (Baralho *)malloc(sizeof(Baralho));
        jogo->bCompra = (Baralho *)malloc(sizeof(Baralho));
        jogo->cicloJogadores->jAtual = noJogador;
    
    return jogo;
}

void proximoNoJogador(Jogo *jogo){
    if(jogo == NULL || jogo->cicloJogadores == NULL || jogo->cicloJogadores->jAtual->prox == NULL){
        printf("Erro: jogo ou nojogador atual são inválidos!");
        return;
    }
    if(jogo->cicloJogadores->isInverso == false){
    printf("mem1: %p\n",jogo->cicloJogadores->jAtual);
    printf("mem2: %p\n",jogo->cicloJogadores->jAtual->manilha);
    jogo->cicloJogadores->jAtual = jogo->cicloJogadores->jAtual->prox;
    printf("mem1: %p\n",jogo->cicloJogadores->jAtual);
    printf("mem2: %p\n",jogo->cicloJogadores->jAtual->manilha);
    }else{
    jogo->cicloJogadores->jAtual = jogo->cicloJogadores->jAtual->ant;
    printf("mem: %p\n",jogo->cicloJogadores);
    }

}

bool isPlayer(Jogo *jogo){
    printf("eero");
    if(jogo->cicloJogadores){
        perror("Erro Crítico: jogador não encontrado!\n");
        exit(1);
    }

    if(jogo->cicloJogadores->jAtual->perfil == NULL|| jogo->cicloJogadores->jAtual->isBot == NULL){
        perror("Erro: perfil do jogador não encontrado");
        return true;
    }
    printf("eero");
    return jogo->cicloJogadores->jAtual->isBot;
}

void distribuirBaralho(Baralho *baralho, Manilha *manilha, int quant) {
    
    for (;quant > 0; quant--) {

        Carta carta = pegarCarta(baralho);

        adicionarNoMalinha(manilha, &carta);
    }
}

Manilha *getManilha(Jogo *jogo) {
    if(jogo->jogadorAtual->mAtual == NULL){
        perror("Erro Crítico: Falha ao encontrar o jogador atual!\n");
        exit(EXIT_FAILURE);
    }

    return jogo->jogadorAtual->mAtual;
}

Carta *enviarManilha(Manilha *manilha, Baralho *baralho){
                printf("man!\n");

    if (baralho == NULL || baralhoVazio(baralho)) {
        perror("Erro Crítico: Baralho Vazio, não foi possível transferir %d Cartas para a manilha\n");
        exit(EXIT_FAILURE);
    }

                        printf("man!\n");

        Carta *carta = &(manilha->carta);
        printf("car: %c\n",carta->categoria);

        printf("man!\n");
        manilha->qtd--;
        if(baralho->topo == BARALHO_SIZE-1) {
            perror("Erro: baralho cheio!\n");
            exit(EXIT_FAILURE);
        }
        printf("man!\n");
        adicionarCarta(baralho, *carta);
        printf("man!\n");
        manilha->ant->prox = manilha->prox->ant;
        manilha->prox->ant = manilha->ant->prox;
                        printf("man!\n");

        free(manilha);
                printf("car: %c\n",carta->categoria);

        return carta;
}

char maiorQtdCor(Jogo *jogo){
    Manilha *manilha = jogo->jogadorAtual->mAtual;
    int numCor[4];
    int maiorQtd;
    int maiorCor;
     
    memset(numCor, 0, sizeof(numCor));
    
    do{
        char *ptr = strchr("RGBY", jogo->jogadorAtual->mAtual->carta.categoria);
        int valor = ptr ? ptr - jogo->jogadorAtual->mAtual->carta.categoria : -1;
        numCor[valor]++;
        manilha = manilha->prox;
    }while(manilha != jogo->jogadorAtual->mAtual);
    
    for(int i = 0;i<4;i++){
        if(numCor[i] > maiorQtd){
            maiorQtd = numCor[i];
            maiorCor = i;
        } 
    }

    return "RGBY"[maiorCor];
}

int poderCarta(Carta *carta, Jogo *jogo){
                printf("poder!\n");
                if(carta == NULL){
                    perror("Erro: Carta não alocada!\n");
                    return -1;
                }

    /*
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
    */
                   printf("poder!\n");

    if(carta->numero < 10){
                        printf("poder, saiu!\n");
        return 0;
    }
    printf("poder, cont!\n");

    switch (carta->numero)
    {
    case 10:
    printf("poder!\n");
        return 2;
        break;
    case 11:
    printf("poder!\n");
        jogo->isInverso = !!jogo->isInverso;
        break;
    case 12:
    printf("poder!\n");
        jogo->jogadorAtual = jogo->jogadorAtual->prox;
        break;
    case 13:
    printf("poder!\n");
    bool prox = false;
    char cor;

    if(isPlayer(jogo) == false){
        srand(time(NULL));
        if(rand() % 6 >= 4){ //40% de chance de escolher uma cor aléatoria 
            jogo->bMesa->cartas[jogo->bMesa->topo].categoria = maiorQtdCor(jogo);
        }else{
            cor = "RGBY"[rand() % 4];
        }
    }

    do{
        printf("Digite a Primeira letra da cor desejada em inglês, sendo repectivamente:\n R - Vermelho, G - Verde, B - Azul, Y - Amarelo\n");
        cor = getchar();
        if(cor == 'R' || cor == 'G' || cor == 'B' || cor == 'Y'){
            jogo->bMesa->cartas[jogo->bMesa->topo].categoria = cor;
            prox = true;
        }else{
            system("clear");
            printf("Entrada Inválida\n Escolha uma cor válida para continuar!\n");
            system("pause");
        }
    }while(prox);
        break;
    case 14:
    printf("poder!\n");
        return 4;
        break;
    }
    printf("poder, foi!\n");
    return 0;
}

void listarNoJogador(Jogo *jogo){
    NoJogador *tempNoJogador = jogo->jogadorAtual;
    if(jogo->jogadorAtual == NULL) return;
    do{
        printf("Memoria: %p\n", *jogo->jogadorAtual);
        jogo->jogadorAtual = jogo->jogadorAtual->prox;
    }while (jogo->jogadorAtual != NULL && jogo->jogadorAtual != tempNoJogador);
}

void adicionarNoJogador(Jogo *jogo, Manilha *manilha, bool _isPlayer) {
    if (jogo == NULL || manilha == NULL) {
        printf("Erro: Jogo ou Manilha não inicializados!\n");
        return;
    }

    if (jogo->jogadorAtual == NULL) {
        printf("Erro: NoJogador não inicializado, falha ao adicionar Manilha ao NoJogador de jogo!\n");
        return;
    }

    NoJogador *novoNo = (NoJogador *)malloc(sizeof(NoJogador));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para novoNo em adicionar NoJogador!\n");
        return;
    }

    novoNo->mAtual = manilha;

    if (jogo->jogadorAtual->prox == NULL){
            
            novoNo->ant = novoNo;
            novoNo->prox = novoNo;
            jogo->jogadorAtual = novoNo;

        } else {

            novoNo->ant = jogo->jogadorAtual->ant;
            novoNo->prox = jogo->jogadorAtual;

            jogo->jogadorAtual->ant->prox = novoNo;
            jogo->jogadorAtual->ant = novoNo;

        }
        
        novoNo->perfil = malloc(sizeof(Perfil));
    if(!_isPlayer) {
        novoNo->perfil->isBot = true;
    }else{
        novoNo->perfil->isBot = false;
    }
    

    jogo->qtdJogadores++;
}

NoJogador *criarNoJogador(){
    NoJogador *nojogador = (NoJogador *)malloc(sizeof(NoJogador));
    if(nojogador == NULL){
        printf("Erro: Falha ao alocar memoria para o nojogador de jogo!\n");
        return NULL;
    } 

    nojogador->prox = NULL;
    nojogador->ant = NULL;
    nojogador->perfil = NULL;

    return nojogador;
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
        baralho_principal->cartas[baralho_principal->topo].categoria = cartas[0][i];
        baralho_principal->cartas[baralho_principal->topo].numero = cartas[1][i];
    }
    
    for (int i = 0; i <= baralho_principal->topo; i++) {
        printf("Carta %d:\n", i + 1);
        printf("Categoria: %c\n", baralho_principal->cartas[i].categoria);
        printf("Número: %d\n\n", baralho_principal->cartas[i].numero);
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
  return &(baralho->cartas[baralho->topo]);
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
    jogo->jogadorAtual->mAtual = jogo->jogadorAtual->mAtual->ant;
    return false;
    break;
  case 'D':
    jogo->jogadorAtual->mAtual = jogo->jogadorAtual->mAtual->prox;
    return false;
    break;
  case 'W':
    if(jogadaValida(&(jogo->jogadorAtual->mAtual->carta),
                    &(jogo->bMesa->cartas[jogo->bMesa->topo]))) {
      enviarManilha(jogo->jogadorAtual->mAtual, jogo->bMesa);
      return true;
    }
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
    if (ptrs == NULL) {
        perror("Erro ao alocar memória\n");
        exit(1);
    }
  
    int *quant = malloc(sizeof(int));
    if (quant == NULL) {
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
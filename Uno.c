#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define getName(var, str)  sprintf(str, "%s", #var) 

#include "Uno.h"

// Coloque: tipoCarta[carta.numero] para retornar o tipo da carta solicitada.

typedef struct noCarta
{
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
    struct noCarta *ant, *prox;

}NoCarta;

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

typedef struct manilha
{
    
    unsigned int qtd;
    NoCarta *mAtual;
    
    NoCarta *inicioAzul;
    NoCarta *inicioVermelho;
    NoCarta *inicioVerde;
    NoCarta *inicioAmarelo;

    NoCarta *inicioCuringa;

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
    bool isUno;

} NoJogador;

typedef struct listaJogadorCircular
{

    NoJogador *jAtual;
    int qtdJogadores;
    int qtdJogadas;
    bool isInverso;

}ListaJogadorCircular;

typedef struct baralho {
    
    NoCarta *cartas[BARALHO_SIZE];
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
void adicionarCarta(Baralho *baralho, NoCarta *carta) {
    if (baralhoCheio(baralho)) {
        printf("Erro: o baralho está cheio\n");
    } else {
        baralho->topo++; // Incrementa o topo
        baralho->cartas[baralho->topo] = carta; // Adiciona a carta à posição do topo
    }
}

// Função para remover uma carta do baralho
NoCarta *pegarCarta(Baralho *baralho) {

    if (baralhoVazio(baralho)) {
        printf("Erro: o baralho está vazio\n");
        return NULL; // Retorna uma carta vazia indicando erro
    }
    

    NoCarta *carta = baralho->cartas[baralho->topo]; // Obtém a carta do topo
    if (carta->numero == 14 || carta->numero == 13){
        carta->categoria = 'J';    
    }
        
    baralho->topo--; // Decrementa o topo
    return carta; // Retorna a carta removida
    
}

void checarLista(Jogo *jogo){
    NoCarta *tempManilha = jogo->cicloJogadores->jAtual->manilha->mAtual;
    int cont = 0;
    for(int f = 1; f <= 2; f++){
    cont = 0;
            if(f == 1){
                printf("\nChecar prox");
                do{
                    if(cont >= 40)
                        system("pause");
                    printf("\n categoria: %c",tempManilha->categoria);
                    printf("\n numero: %d",tempManilha->numero);
                    cont++;
                    tempManilha = tempManilha->prox;
                }while(tempManilha != jogo->cicloJogadores->jAtual->manilha->mAtual);
            }else{
                printf("\nChecar ant");
                do{
                    if(cont >= 40)
                        system("pause");
                    printf("\n categoria: %c",tempManilha->categoria);
                    printf("\n numero: %d",tempManilha->numero);
                    cont++;
                    tempManilha = tempManilha->ant;
                }while(tempManilha != jogo->cicloJogadores->jAtual->manilha->mAtual);
            
            }
    }
        
}

void listarBaralho(Baralho *cartas){
    
    for(int i = 0; i <= cartas->topo; i++)
        printf("Número: %d, Categoria: %c\n", cartas->cartas[i]->numero, cartas->cartas[i]->categoria);
    
}

void listarManilha(Manilha *cartas) {
    Manilha *carta = cartas;
    do{
        printf("Número: %s, Categoria: %c\n", tipoCarta[cartas->mAtual->numero], cartas->mAtual->categoria);
        printf("quantidade: %d\n",cartas->qtd);
        cartas->mAtual = cartas->mAtual->prox;
    }while (cartas != NULL && cartas != carta);
}

Manilha *criarManilha() {
    Manilha *manilha = (Manilha*)malloc(sizeof(Manilha));
    printf("criarManil");
        if(!manilha){
        perror("Erro: falha ao alocar espaço para manilha");
        exit(EXIT_FAILURE);
    }
    manilha->qtd = 0;
    manilha->mAtual = NULL;

    manilha->inicioVermelho = NULL;
    manilha->inicioVerde = NULL;
    manilha->inicioAmarelo = NULL;
    manilha->inicioAzul = NULL;
    manilha->inicioCuringa = NULL;


    return manilha;
}

NoCarta *slotOrdemManilha(Manilha *manilha, char cor) {
    switch(cor)
    {
        case 'R':
            printf("R");
            return manilha->inicioVermelho;
        case 'G':
            printf("G");
            return manilha->inicioVerde;
        case 'B':
            printf("B");
            return manilha->inicioAzul;
        case 'Y':
            printf("Y");
            return manilha->inicioAmarelo;
        case 'J':
            printf("J");
            return manilha->inicioCuringa;
    }
}

void adicionarManilhaAtualSlotCor(Manilha *manilha, NoCarta *carta){
    if(carta->categoria == 'R'){
            printf("R");
            manilha->inicioVermelho = carta;
            printf("%p",manilha->inicioVermelho->prox);
    }else if(carta->categoria == 'G'){
            printf("G");
            manilha->inicioVerde = carta;
            printf("%p",manilha->inicioVerde->prox);
    }else if(carta->categoria == 'B'){
            printf("B");
            manilha->inicioAzul = carta;
            printf("%p",manilha->inicioAzul->prox);
    }else if(carta->categoria == 'Y'){
            printf("Y");
            manilha->inicioAmarelo = carta;
            printf("%p",manilha->inicioAmarelo->prox);
    }else if(carta->categoria == 'J'){
            printf("J");
            manilha->inicioCuringa = carta;
            printf("%p",manilha->inicioCuringa->prox);
    }else
    {
    exit(1);
    }

}

bool slotCorVazio(Manilha *manilha, char cor){
    printf("1");
    
    if(cor == 'R'){
            printf("R");
            if(manilha->inicioVermelho == NULL)
            return true;
            printf("returnFalse");
    }else if(cor == 'G'){
            printf("G");
            if(manilha->inicioVerde == NULL)
            return true;
            printf("returnFalse");
    }else if(cor == 'B'){
            printf("B");
            if(manilha->inicioAzul == NULL)
            return true;
            printf("returnFalse");
    }else if(cor == 'Y'){
            printf("Y");
            if(manilha->inicioAmarelo == NULL)
            return true;
            printf("returnFalse");
    }else if(cor == 'J'){
            printf("J");
            if(manilha->inicioCuringa == NULL)
            return true;
            printf("returnFalse");
            
    }
    return false;
    
}

void adicionarNoMalinha(Manilha *manilha, NoCarta *carta) {
    
    char cor[5] = "RGBYJ";
    if(!manilha || !carta)
    {
        perror("Erro: Manilha não alocada!");
        exit(EXIT_FAILURE);
    }
    carta->prox = carta;
    carta->ant = carta;
    if(!carta->prox)
    {
        perror("Erro: Falha ao alocar no carta->prox!");
        exit(EXIT_FAILURE);
    }

    
    manilha->qtd++;
    
    NoCarta *corAtual = slotOrdemManilha(manilha, carta->categoria);
    manilha->mAtual = carta;
    manilha->mAtual->prox = manilha->mAtual;
    manilha->mAtual->ant = manilha->mAtual;
    if(slotCorVazio(manilha, carta->categoria))
    {
        adicionarManilhaAtualSlotCor(manilha, carta);
        char *posicao = strchr(cor, carta->categoria);
        int indice = posicao - cor;

        for(int i = 1;; i++)
        {
            int newIndex = (indice + i) % sizeof(cor) / sizeof(cor[0]);
            printf("\nteste");
            printf("%c", carta->categoria);
            if(!slotCorVazio(manilha, cor[newIndex]) || cor[newIndex] == carta->categoria)
            {  
                NoCarta *tempCarta;
                
                switch(cor[newIndex]){
                    case 'R':
                    tempCarta = manilha->inicioVermelho;
                    break;
                    case 'G':
                    tempCarta = manilha->inicioVerde;
                    break;
                    case 'B':
                    tempCarta = manilha->inicioAzul;
                    break;
                    case 'Y':
                    tempCarta = manilha->inicioAmarelo;
                    break;
                    case 'J':
                    tempCarta = manilha->inicioCuringa;
                    break;
                }

                printf("%p",tempCarta->ant);

                tempCarta->ant->prox = manilha->mAtual;
                manilha->mAtual->ant = tempCarta->ant;
                tempCarta->ant = manilha->mAtual;
                manilha->mAtual->prox = tempCarta;

                printf("\nArlos\n");
                break;
            }

        }
                    
    EXITLOOP:
        
    }
    else
    {
        printf("\nestado 4!");
        
        NoCarta *tempManilha = corAtual;
        printf("\nCategoria: %c\n", corAtual->categoria);
        printf("Num: %d\n", corAtual->numero);
        
        if(carta == NULL){
            perror("Erro carta é NULL");
            exit(EXIT_FAILURE);
        }
            
        for(;;){
            tempManilha = tempManilha->prox;
            printf("\n1Categoria: %c\n", carta->categoria);
            printf("Num: %d\n", carta->numero);

            printf("\n2Categoria: %c\n", tempManilha->categoria);
            printf("Num: %d\n", tempManilha->numero);
            if( carta->categoria != tempManilha->categoria ||
                carta->numero > tempManilha->numero ||
                tempManilha == corAtual)
            {
                    tempManilha->ant->prox = carta;
                    carta->ant = tempManilha->ant;
                    tempManilha->ant = carta;
                    carta->prox = tempManilha;
                    break;
            }
        }
    }
}

Baralho *getBaralhoCompra(Jogo *jogo){
    return jogo->bCompra;
}

Baralho *getBaralhoMesa(Jogo *jogo){
    return jogo->bMesa;
}

Jogo *criarJogo(){
        Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
        
        if(jogo == NULL){ 
            printf("Erro: falha ao alocar memória para Jogo.\n");
            return NULL;
        }
        jogo->bCompra = gerarBaralho();
        jogo->bMesa = criarBaralho();
        jogo->cicloJogadores = criarCiclo();
        int cartaInt = jogo->bCompra->topo;

        for(;jogo->bCompra->cartas[cartaInt]->numero > 12; cartaInt--);

        NoCarta *cartaAux = jogo->bCompra->cartas[cartaInt];
        jogo->bCompra->cartas[cartaInt] = jogo->bCompra->cartas[jogo->bCompra->topo];
        jogo->bCompra->cartas[jogo->bCompra->topo] = cartaAux;
        printf("2");
        NoCarta *carta = pegarCarta(jogo->bCompra);
        adicionarCarta(jogo->bMesa, carta);
        
    
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
    printf("mem1: %p\n",jogo->cicloJogadores->jAtual);
    printf("mem2: %p\n",jogo->cicloJogadores->jAtual->manilha);
    jogo->cicloJogadores->jAtual = jogo->cicloJogadores->jAtual->ant;
    printf("mem1: %p\n",jogo->cicloJogadores->jAtual);
    printf("mem2: %p\n",jogo->cicloJogadores->jAtual->manilha);
    }

}

bool isPlayer(Jogo *jogo){
    printf("eero");
    if(!jogo->cicloJogadores->jAtual){
        perror("Erro Crítico: jogador não encontrado!\n");
        exit(EXIT_FAILURE);
    }

    if(!jogo->cicloJogadores->jAtual->perfil){
        perror("Erro: perfil do jogador não encontrado");
        exit(EXIT_FAILURE);
    }
    printf("eero");
    return jogo->cicloJogadores->jAtual->isBot;
}

void distribuirBaralho(Baralho *baralho, NoJogador *noJogador, int quant) {
    printf("\n1");
    for (;quant > 0; quant--) {
        printf("\n2");
        NoCarta *carta = pegarCarta(baralho);

        if(&carta == NULL){
            perror("Erro: Carta do Baralho é NULL");
            exit(EXIT_FAILURE);
        }
        printf("\n3");
        adicionarNoMalinha(noJogador->manilha, carta);
        printf("\n4");
    }
}

NoCarta *getCartaMesa(Jogo *jogo){
    if(!baralhoVazio(jogo->bMesa))
    return jogo->bMesa->cartas[jogo->bMesa->topo];
}

Manilha *getManilha(Jogo *jogo) {
    if(jogo->cicloJogadores->jAtual == NULL){
        perror("Erro Crítico: Falha ao encontrar o jogador atual!\n");
        exit(EXIT_FAILURE);
    }

    return jogo->cicloJogadores->jAtual->manilha;
}

bool manilhaVazia(Jogo *jogo){
    return jogo->cicloJogadores->jAtual->manilha->qtd == 0;
}

NoCarta *pegarCartaManilha(Manilha *manilha) {
    printf("pegarCartaManilha Entrada\n");

    NoCarta *tempNoCarta;
    switch (manilha->mAtual->categoria)
    {
    case 'R':
        tempNoCarta = manilha->inicioVermelho;
        break;
    case 'G':
        tempNoCarta = manilha->inicioVerde;
        break;
    case 'B':
        tempNoCarta = manilha->inicioAzul;
        break;
    case 'Y':
        tempNoCarta = manilha->inicioAmarelo;
        break;
    case 'J':
        tempNoCarta = manilha->inicioCuringa;
        break;
    }
    if(tempNoCarta == manilha->mAtual)
    {  
    if(tempNoCarta->prox->categoria == manilha->mAtual->categoria){
    switch (manilha->mAtual->categoria)
    {
    case 'R':
        manilha->inicioVermelho = manilha->inicioVermelho->prox;
        break;
    case 'G':
        manilha->inicioVerde = manilha->inicioVerde->prox;
        break;
    case 'B':
        manilha->inicioAzul = manilha->inicioAzul->prox;
        break;
    case 'Y':
        manilha->inicioAmarelo = manilha->inicioAmarelo->prox;
        break;
    case 'J':
        manilha->inicioCuringa = manilha->inicioCuringa->prox;
        break;
    }
    }
    else
    {
        switch (manilha->mAtual->categoria)
    {
    case 'R':
        manilha->inicioVermelho = NULL;
        break;
    case 'G':
        manilha->inicioVerde = NULL;
        break;
    case 'B':
        manilha->inicioAzul = NULL;
        break;
    case 'Y':
        manilha->inicioAmarelo = NULL;
        break;
    case 'J':
        manilha->inicioCuringa = NULL;
        break;
    }
    }
    }

    if (manilha->qtd == 0) {
        // If the manilha is empty, return an invalid card
        return NULL;
    }

    NoCarta *carta = manilha->mAtual;
    NoCarta *tempManilha = manilha->mAtual;
    
    manilha->mAtual = manilha->mAtual->prox;

    // If there's only one node in the manilha, reset it
    if (manilha->qtd == 1) {
        manilha->mAtual = NULL;
    } else {
        tempManilha->ant->prox = tempManilha->prox;
        tempManilha->prox->ant = tempManilha->ant;

        tempManilha->ant = NULL;
        tempManilha->prox = NULL;
    }

    manilha->qtd--;
    printf("pegarCartaManilha Saida\n");
    return carta;
}

NoCarta *enviarManilha(Manilha *manilha, Baralho *baralho) {
    if (baralho == NULL || baralhoVazio(baralho)) {
        perror("Erro Crítico: Baralho Vazio, não foi possível transferir Cartas para a manilha\n");
        exit(EXIT_FAILURE);
    }

    NoCarta *carta = pegarCartaManilha(manilha);

    if (carta == NULL) {
        perror("Erro: Carta é NULL");
        exit(EXIT_FAILURE);
    }

    adicionarCarta(baralho, carta);
    return baralho->cartas[baralho->topo];
}

char maiorQtdCor(Jogo *jogo) {
    Manilha *manilha = jogo->cicloJogadores->jAtual->manilha;
    int numCor[4] = {0}; // Inicializa com 0
    int maiorQtd = -1; // Inicializa com um valor menor que qualquer possível em numCor
    int maiorCor = 0;
    char cor[4] = "RGBY";
    
    do {
        if (manilha->mAtual->categoria == 'J') {
            manilha->mAtual = manilha->mAtual->prox;
            continue;
        }
        
        char *posicao = strchr(cor, manilha->mAtual->categoria);
        if (posicao != NULL) {
            int valor = posicao - cor;
            numCor[valor]++;
        }

        manilha->mAtual = manilha->mAtual->prox;
    } while (manilha->mAtual != jogo->cicloJogadores->jAtual->manilha->mAtual);

    for (int i = 0; i < 4; i++) {
        if (numCor[i] > maiorQtd) {
            maiorQtd = numCor[i];
            maiorCor = i;
        }
    }

    printf("maior: %c\n", cor[maiorCor]);
    return cor[maiorCor];
}

int poderCarta(NoCarta *carta, Jogo *jogo) {
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
    case 11:
    printf("poder!\n");
        jogo->cicloJogadores->isInverso = !!jogo->cicloJogadores->isInverso;
        break;
    case 12:
    printf("poder!\n");
        jogo->cicloJogadores->jAtual = jogo->cicloJogadores->jAtual->prox;
        break;
    case 13:
    printf("poder!\n");
            alterarCorCarta(jogo, carta);
        break;
    case 14:
    printf("poder!\n");
            alterarCorCarta(jogo, carta);
            return 4;
    }
    printf("poder, foi!\n");
    return 0;
}

void alterarCorCarta(Jogo *jogo, NoCarta *carta){
    bool prox = false;
    char cor;
    system("cls");
    if(isPlayer(jogo) == false){
        srand(time(NULL));
        if((rand() % 10) <= 3){ //40% de chance de escolher uma cor aléatoria 
            printf("\nranddaw");
            jogo->bMesa->cartas[jogo->bMesa->topo]->categoria = maiorQtdCor(jogo);
            printf("\nranddaw2");
        }else{
            printf("rataria");
            cor = "RGBY"[rand() % 4];
            carta->categoria = cor;
        }
    }
    else do{
        
        printf("Digite a Primeira letra da cor desejada em inglês, sendo repectivamente:\n R - Vermelho, G - Verde, B - Azul, Y - Amarelo\n");
        cor = _getch();
        if(cor == 'R' || cor == 'G' || cor == 'B' || cor == 'Y'){
            carta->categoria = cor;
            prox = true;
        }else{
            system("cls");
            printf("Entrada Inválida\n Escolha uma cor válida para continuar!\n");
        }
    }while(!prox);
}

void listarNoJogador(Jogo *jogo){
    if(jogo->cicloJogadores == NULL) return;
    NoJogador *tempJogador = jogo->cicloJogadores->jAtual;
    do{
        if(tempJogador->isBot){
            printf("\n(Player) ->");
        }else{
            printf("(Bot) ->");
        }
        tempJogador = tempJogador->prox;
    }while (tempJogador != jogo->cicloJogadores->jAtual);
}

void adicionarNoJogador(Jogo *jogo, NoJogador *noJogador, bool _isPlayer) {
    if (jogo == NULL || noJogador == NULL) {
        printf("Erro: Jogo ou noJogador não inicializados!\n");
        return;
    }
    
    printf("teste");
    if (jogo->cicloJogadores->jAtual == NULL){
        jogo->cicloJogadores->jAtual = noJogador;

    } else {
            
        jogo->cicloJogadores->jAtual->ant->prox = noJogador;
        noJogador->ant = jogo->cicloJogadores->jAtual->ant;         
        jogo->cicloJogadores->jAtual->ant = noJogador;
        noJogador->prox = jogo->cicloJogadores->jAtual;
            
    }

    jogo->cicloJogadores->qtdJogadores++;
}

NoJogador *criarNoJogador(bool _isPlayer) {
    NoJogador *nojogador = (NoJogador *)malloc(sizeof(NoJogador));

    if(nojogador == NULL){
        perror("Erro: Falha ao alocar memoria para o nojogador de jogo!\n");
        return NULL;
    } 

    nojogador->prox = nojogador;
    nojogador->ant = nojogador;
    nojogador->perfil = (Perfil *)malloc(sizeof(Perfil));
    nojogador->isBot = _isPlayer;
    nojogador->manilha = criarManilha();
    nojogador->isUno = false;

    return nojogador;
}

ListaJogadorCircular *criarCiclo(){
    ListaJogadorCircular *listaJogadorCircular = (ListaJogadorCircular *)malloc(sizeof(ListaJogadorCircular));
    if(listaJogadorCircular == NULL){
        perror("Erro: Falha ao alocar memoria para a Lista Jogador de jogo!\n");
        exit(EXIT_FAILURE);
    }

    listaJogadorCircular->isInverso = false;
    listaJogadorCircular->jAtual = NULL;
    listaJogadorCircular->qtdJogadas = 0;
    listaJogadorCircular->qtdJogadores = 0;
    return listaJogadorCircular;
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
        exit(EXIT_FAILURE);
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

    printf("teste\n");

    Baralho* baralho_principal = (Baralho*)malloc(sizeof(Baralho));
    if (baralho_principal == NULL) {
        printf("Erro: ao alocar memória para o baralho!\n");
        return NULL;
    }

    baralho_principal->topo = -1;
    NoCarta *tempCarta; 
    for (int i = 0; i < BARALHO_SIZE; i++) {
        tempCarta =  (NoCarta *)malloc(sizeof(NoCarta));
        tempCarta->categoria = cartas[0][i];
        tempCarta->numero = cartas[1][i];
        baralho_principal->topo++;
        baralho_principal->cartas[baralho_principal->topo] = tempCarta;
    }
    
    for (int i = 0; i <= baralho_principal->topo; i++) {
        printf("Carta %d:\n", i + 1);
        printf("Categoria: %c\n", baralho_principal->cartas[i]->categoria);
        printf("Número: %d\n\n", baralho_principal->cartas[i]->numero);
    }


    return baralho_principal;
}

void reembaralhar(Baralho *baralho, Baralho *mesa){
    NoCarta *topo_mesa = pegarCarta(mesa);
    int tamanho_vetor = mesa->topo + 1;
    NoCarta *vetor[tamanho_vetor];
    int i = 0;
    while(!baralhoVazio(mesa)){
        vetor[i] = pegarCarta(mesa);
        i++;
    }
    NoCarta *temp;
    for(int i = 0, j = (tamanho_vetor-1); i <= j; i++, j--){
        int random_num = rand() % (tamanho_vetor-1);
        
        temp->categoria = vetor[i]->categoria;
        temp->numero = vetor[i]->numero;

        vetor[i]->categoria = vetor[random_num]->categoria;
        vetor[i]->numero = vetor[random_num]->numero;
        
        vetor[random_num]->categoria = temp->categoria;
        vetor[random_num]->numero = temp->numero;

        random_num = rand() % (tamanho_vetor-1);
        
        temp->categoria = vetor[j]->categoria;
        temp->numero = vetor[j]->numero;
        
        vetor[j]->categoria = vetor[random_num]->categoria;
        vetor[j]->numero = vetor[random_num]->numero;
        
        vetor[random_num]->categoria = temp->categoria;
        vetor[random_num]->numero = temp->numero;
    
    }
    for(int i = 0; i < tamanho_vetor; i++){
        adicionarCarta(baralho, vetor[i]);
    }
    adicionarCarta(mesa, topo_mesa);
}

NoCarta *topoBaralho(Baralho *baralho) {
  if (baralho == NULL) {
    printf("Erro: baralho não inicializado\n");
    exit(EXIT_FAILURE);
  }
  return baralho->cartas[baralho->topo];
}

bool jogadaValida(NoCarta *pCarta, NoCarta *mCarta) {
    if(pCarta == NULL){
        perror("Erro: pCarta não inicializada!\n");
    }
    if(mCarta == NULL){
        perror("Erro: mCarta não inicializada!\n");
    }
    printf("\nplayer Carta \nCor: %c Núumero: %d\n",pCarta->categoria,pCarta->numero);
    printf("\nmesa Carta \nCor: %c Núumero: %d\n",mCarta->categoria,mCarta->numero);
  if (pCarta->categoria == mCarta->categoria || 
      pCarta->categoria == 'J' ||
      pCarta->numero == mCarta->numero){
        printf("jogadaValida saiuda\n");
        return true;
    }
        printf("jogadaInvalida saiuda\n");

    return false;
}

void playerUnoThread(NoJogador *noJogador){
    do{
        char comando = '\0';
        bool playerVerificado = false;
        NoJogador *auxNoJogador = noJogador;
        do{
            comando = _getch();
        }while(comando == ' ');
        do{
            if(noJogador->isBot == false){
                if(auxNoJogador->manilha->qtd == 1 && noJogador->isUno == true){
                    noJogador->isUno = false;
                    break;
                }
                playerVerificado = true;
                noJogador = auxNoJogador;
            }
            if(noJogador->isBot == true && playerVerificado == true && noJogador->manilha->qtd == 1 && noJogador->isUno == true){
                printf("\n!UNO!\n Você gritou UNO!\nE um bot teve que comprar uma carta!\n");
            }
            auxNoJogador = auxNoJogador->prox;
        }while(auxNoJogador != noJogador);
    }while(false != true);
}

void unoThread(NoJogador *noJogador, Jogo *jogo){
    noJogador->isUno == true;
    
    srand(time(NULL));
    
    _sleep((rand() % 4) + 2);
    
    if(noJogador->manilha->qtd != 1) {
        noJogador->isUno = false;
        return;
    }
    
    if(noJogador->isBot == true && rand() % 10 < 7 && noJogador->manilha->qtd == 1){
    
        printf("\n!UNO!\n Bot gritou UNO!\nE ele está com uma carta!\n");
        noJogador->isUno == false;
        system("pause");
        return;
    }

    if(noJogador->isUno == true && noJogador->manilha->qtd == 1){
        
        system("cls");
        if(noJogador->isBot == false){
            printf("\n!UNO!\n Bot gritou UNO!\nvocê teve que comprar uma carta!\n");
        }else{
            printf("\n!UNO!\n Bot gritou UNO!\nE um bot teve que comprar uma carta!\n");
        }

        NoCarta *cartaComprada = pegarCartaCompra(getBaralhoMesa(jogo), getBaralhoCompra(jogo));
        adicionarNoMalinha(jogo->cicloJogadores->jAtual->manilha, cartaComprada);
        printf("\nCarta Uno Comprada\n");
        printCarta(jogo->cicloJogadores->jAtual->manilha);

        noJogador->isUno = false;
        system("pause");
        return;
    }

}

NoCarta *contarComprarMais2(NoCarta *noCarta) {
    if (noCarta == NULL) return NULL;

    NoCarta *tempNoCarta = NULL;
    int count = 0;
    NoCarta *auxNoCarta = noCarta;

    do {
        if (auxNoCarta->numero == 10) {
            count++;
            NoCarta *newTemp = realloc(tempNoCarta, sizeof(NoCarta) * count);
            if (newTemp == NULL) {
                free(tempNoCarta); // Libera memória em caso de falha
                return NULL;
            }
            tempNoCarta = newTemp;
            tempNoCarta[count + 1] = *auxNoCarta;
        }
        auxNoCarta = auxNoCarta->prox;
    } while (auxNoCarta != noCarta);

    return tempNoCarta;
}


// Função para verificar se há cartas disponíveis
bool verificarComprarCarta(Jogo *jogo, int *compra) {
    system("cls");

    if (jogo->bMesa->cartas[jogo->bMesa->topo]->numero == 10) {
        printf("Compra Sendo realizada!");
        system("pause");
        NoCarta *cartas = contarComprarMais2(jogo->cicloJogadores->jAtual->manilha->mAtual);
        printf("2");
        system("pause");
        if (cartas != NULL) {
            char comando;
            do {
                printf("\nContinuar a corrente de +2 ? (S/N)\n");
                fflush(stdin);
                comando = _getch();
            } while (comando != 'S' && comando != 'N');

            if (comando == 'S') {
                int count = 0;
                do {
                    system("cls");
                    printf("\nQual carta você deseja Lançar? (A - Esquerda, D - Direita, W - Jogar Carta)\n");
                    printf("\nMão \n Categoria: %c Tipo: %d\n", cartas[count].categoria, cartas[count].numero);
                    printf("\nMesa \n Categoria: %c Tipo: %d\n", jogo->bMesa->cartas[jogo->bMesa->topo]->categoria, jogo->bMesa->cartas[jogo->bMesa->topo]->numero);

                    comando = _getch();
                    if (comando == 'a' && count > 0) {
                        count--;
                    } else if (comando == 'd' && count < (sizeof(cartas)/sizeof(NoCarta))) { // Verifica se há próxima carta
                        count++;
                    }
                } while (comando != 'w' && comando != 'W');

                adicionarCarta(jogo->bMesa, &cartas[count]);
                (*compra) += 2;
                free(cartas); // Libera memória alocada
                return false;
            }
            free(cartas); // Libera memória alocada
        }
    }

    for (; *compra > 0; (*compra)--) {
        NoCarta *cartaComprada = pegarCartaCompra(getBaralhoMesa(jogo), getBaralhoCompra(jogo));
        adicionarNoMalinha(jogo->cicloJogadores->jAtual->manilha, cartaComprada);
        printf("\nCarta Comprada[%d]\n", *compra);
        printCarta(jogo->cicloJogadores->jAtual->manilha);
    }



    if (jogo->bMesa->cartas[jogo->bMesa->topo]->categoria == 14) {
        return true;
    }
    return false;
}

int selecionarCarta(char tecla, Jogo *jogo) {
  switch (tecla) {
  case 'A': case 'a':
    jogo->cicloJogadores->jAtual->manilha->mAtual = jogo->cicloJogadores->jAtual->manilha->mAtual->ant;
    printf("\n\nMesa: ");
    printf("Numero: %d ", jogo->bMesa->cartas[jogo->bMesa->topo]->numero);
    printf("Cor: %c \n", jogo->bMesa->cartas[jogo->bMesa->topo]->categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->categoria);
    return -1;
  case 'D': case 'd':
    jogo->cicloJogadores->jAtual->manilha->mAtual = jogo->cicloJogadores->jAtual->manilha->mAtual->prox;
    printf("\n\nMesa: ");
    printf("Numero: %d ", jogo->bMesa->cartas[jogo->bMesa->topo]->numero);
    printf("Cor: %c \n", jogo->bMesa->cartas[jogo->bMesa->topo]->categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->categoria);
    return -1;
  case 'W': case 'w':
    NoCarta *tempCarta = jogo->bMesa->cartas[jogo->bMesa->topo];
    printf("\n\nMesa: ");
    printf("Numero: %d ", tempCarta->numero);
    printf("Cor: %c \n", tempCarta->categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->categoria);
    if(jogadaValida(jogo->cicloJogadores->jAtual->manilha->mAtual,
                    jogo->bMesa->cartas[jogo->bMesa->topo])) 
    {
      NoCarta *noCarta = enviarManilha(jogo->cicloJogadores->jAtual->manilha, jogo->bMesa);
      return poderCarta(noCarta, jogo);
    }
    printf("Jogada Inválida");
    return -1;

    break;
  case 'S': case 's':
    void **ptrs = cartasJogaveis(topoBaralho(jogo->bMesa), jogo->cicloJogadores->jAtual->manilha);
    int *cQtd = (int *)ptrs[0];
    if(*cQtd <= 0){

        START:
        NoCarta *carta = comprarCarta(jogo);
        if(carta->numero != -1);
        if(!jogadaValida(carta, jogo->bMesa->cartas[jogo->bMesa->topo])){
            system("cls");
            printf("CartaJogada não Valida!\n Precione 'S' novamente para comprar outra carta!");
            fflush(stdin);
            char comando = _getch();
            if(comando == 's' || comando == 'S')
            goto START;
        }   

    }
    return -1;
  }
  return -1;
}

void abastercerBaralho(Baralho *baralhoReceptor, Baralho *baralhoDoador){
    NoCarta *cartaAux;

    cartaAux = baralhoDoador->cartas[baralhoDoador->topo];
    baralhoDoador->cartas[baralhoDoador->topo] = baralhoDoador->cartas[0];
    baralhoDoador->cartas[0] = cartaAux;

    for(; baralhoDoador->topo > 0;){

        printf("PEGOU CARTA ABSTERCER!!!");
<<<<<<< HEAD
        cartaAux = pegarCarta(baralhoDoador);
        adicionarCarta(baralhoReceptor, cartaAux);
=======
	    //Usar FIFO
        carta = pegarCarta(baralhoDoador);
        adicionarCarta(baralhoReceptor, carta);
>>>>>>> 80249b959355d656bfb412c69355ab0aef3a4f5a

    }
    printf("saiu");
}

NoCarta *pegarCartaCompra(Baralho *baralhoMesa, Baralho *baralhoCompra){
        printf("\npegarCartaCompra");
        NoCarta *carta = pegarCarta(baralhoCompra);

        if(carta == NULL && baralhoMesa->topo > 0){
            abastercerBaralho(baralhoCompra, baralhoMesa);
            carta = pegarCarta(baralhoCompra);
        }

        return carta;
    
}

bool comprarCartaBot(Jogo *jogo){
    for(;;){
        printf("Sem Carta Necessaria");
        NoCarta *cartaComprada = comprarCarta(jogo);        
        if(cartaComprada->numero == -1)
        {
            printf("Baralho da Mesa e Baralha compra vazios!\n Passando a vez!");
            return false;
        }
        if(jogadaValida(cartaComprada, getCartaMesa(jogo))){
            return true;
        }
    }
}


NoCarta *comprarCarta(Jogo *jogo){
    
    Manilha *manilha = jogo->cicloJogadores->jAtual->manilha;
    Baralho *baralhoMesa = jogo->bMesa;
    Baralho *baralhoCompra = jogo->bCompra;
    printf("\ncomprarCarta");
    NoCarta *carta = pegarCartaCompra(baralhoMesa, baralhoCompra);
    if(carta == NULL){
        printf("comprarCarta return NULL");
        exit(EXIT_FAILURE);
    }
    adicionarNoMalinha(manilha, carta);

    return carta;
}

void **cartasJogaveis(NoCarta *topo, Manilha *atual){
    void **ptrs = malloc(sizeof(void *));
    
    if (ptrs == NULL) {
        perror("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
  
    int *quant = malloc(sizeof(int));
    if (quant == NULL) {
        perror("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    if(atual == NULL){
        perror("Erro: manilha não alocada!\n");
        exit(EXIT_FAILURE);
    }
    
    *quant = 0;
    NoCarta *tempMani = atual->mAtual;
    printf("\n\n\nPega Visão\n\n\n\n\n\n\n");
    do{
        if(&atual->mAtual == NULL){
            perror("Erro: carta NULL");
            exit(EXIT_FAILURE);
        }

        if(jogadaValida(tempMani, topo)){
            
        (*quant)++;
        ptrs = realloc(ptrs, sizeof(void *) * ((*quant)+1));
        ptrs[*quant] = atual;

      }

      tempMani = tempMani->prox;
    }while(atual->mAtual != tempMani);
    ptrs[0] = quant;

    return ptrs;
}

void printCarta(Manilha *manilha) {
    if(manilha == NULL) {
        perror("Erro: Carta vazia!\n");
        return;
    }

    printf("Carta:\ncategoria: %c\n", manilha->mAtual->categoria);
    printf("numero: %d\n\n", manilha->mAtual->numero);
}

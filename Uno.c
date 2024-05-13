#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define getName(var, str)  sprintf(str, "%s", #var) 

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
        Carta cartaVazia; // Carta vazia para indicar erro
        cartaVazia.numero = -1;
        return cartaVazia; // Retorna uma carta vazia indicando erro
    }
    

    Carta carta = baralho->cartas[baralho->topo]; // Obtém a carta do topo
    if (carta.numero == 14 || carta.numero == 13){
        carta.categoria = 'J';    
    }
        
    baralho->topo--; // Decrementa o topo
    return carta; // Retorna a carta removida
    
}

void checarLista(Jogo *jogo){
    NoManilha *tempManilha = jogo->cicloJogadores->jAtual->manilha->mAtual;
    int cont = 0;
    for(int f = 1; f <= 2; f++){
    cont = 0;
            if(f == 1){
                printf("\nChecar prox");
                do{
                    if(cont >= 40)
                        system("pause");
                    printf("\n categoria: %c",tempManilha->carta.categoria);
                    printf("\n numero: %d",tempManilha->carta.numero);
                    cont++;
                    tempManilha = tempManilha->prox;
                }while(tempManilha != jogo->cicloJogadores->jAtual->manilha->mAtual);
            }else{
                printf("\nChecar ant");
                do{
                    if(cont >= 40)
                        system("pause");
                    printf("\n categoria: %c",tempManilha->carta.categoria);
                    printf("\n numero: %d",tempManilha->carta.numero);
                    cont++;
                    tempManilha = tempManilha->ant;
                }while(tempManilha != jogo->cicloJogadores->jAtual->manilha->mAtual);
            
            }
    }
        
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

NoManilha *slotOrdemManilha(Manilha *manilha, char cor) {
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

void adicionarManilhaAtualSlotCor(Manilha *manilha, Carta carta){
    char cor = carta.categoria;
    if(cor == 'R'){
            printf("R");
            printf(" %p ", manilha->inicioVermelho);
            manilha->inicioVermelho = manilha->mAtual;
            printf(" %p ", manilha->inicioVermelho);
    }else if(cor == 'G'){
            printf("G");
            manilha->inicioVerde = manilha->mAtual;
    }else if(cor == 'B'){
            printf("B");
            manilha->inicioAzul = manilha->mAtual;
    }else if(cor == 'Y'){
            printf("Y");
            manilha->inicioAmarelo = manilha->mAtual;
    }else if(cor == 'J'){
            printf("J");
            manilha->inicioCuringa = manilha->mAtual;
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

void adicionarNoMalinha(Manilha *manilha, Carta *carta) {
    
    char cor[5] = "RGBYJ";
    if(!manilha || !carta)
    {
        perror("Erro: Manilha não alocada!");
        exit(EXIT_FAILURE);
    }
    NoManilha *noManilha = (NoManilha *)malloc(sizeof(NoManilha));
    if(!noManilha)
    {
        perror("Erro: Falha ao alocar no Manilha!");
        exit(EXIT_FAILURE);
    }
    printf("\nestado 1!");
    noManilha->carta = *carta;
    printf("\nestado 1.5!");
    manilha->qtd++;
    printf("\nestado 1!");
    NoManilha *corAtual = slotOrdemManilha(manilha, carta->categoria);
    printf("\nestado 2!");
    
    manilha->mAtual = noManilha;
    manilha->mAtual->prox = manilha->mAtual;
    manilha->mAtual->ant = manilha->mAtual;
    if(slotCorVazio(manilha, noManilha->carta.categoria))
    {
        printf("\nestado 365632634!");
        adicionarManilhaAtualSlotCor(manilha, *carta);
        printf("\nestado 4!");
        char *posicao = strchr(cor, carta->categoria);
        printf("\nestado 5!");
        int indice = posicao - cor;
        printf("\nestado 6!");
        for(int i = 1;; i++)
        {
            printf("\nestado 7!");
            int newIndex = (indice + i) % sizeof(cor) / sizeof(cor[0]);
            printf("teste");
            printf("%c", carta->categoria);
            if(!slotCorVazio(manilha, cor[newIndex]) || cor[newIndex] == carta->categoria)
            {  
                
                switch(cor[newIndex]){
                    case 'R':
                    manilha->inicioVermelho->ant->prox = manilha->mAtual;
                    manilha->mAtual->ant = manilha->inicioVermelho->ant;
                    manilha->inicioVermelho->ant = manilha->mAtual;
                    manilha->mAtual->prox = manilha->inicioVermelho;
                    goto EXITLOOP;
                    case 'G':
                    manilha->inicioVerde->ant->prox = manilha->mAtual;
                    manilha->mAtual->ant = manilha->inicioVerde->ant;
                    manilha->inicioVerde->ant = manilha->mAtual;
                    manilha->mAtual->prox = manilha->inicioVerde;
                    goto EXITLOOP;
                    case 'B':
                    manilha->inicioAzul->ant->prox = manilha->mAtual;
                    manilha->mAtual->ant = manilha->inicioAzul->ant;
                    manilha->inicioAzul->ant = manilha->mAtual;
                    manilha->mAtual->prox = manilha->inicioAzul;
                    goto EXITLOOP;
                    case 'Y':
                    manilha->inicioAmarelo->ant->prox = manilha->mAtual;
                    manilha->mAtual->ant = manilha->inicioAmarelo->ant;
                    manilha->inicioAmarelo->ant = manilha->mAtual;
                    manilha->mAtual->prox = manilha->inicioAmarelo;
                    goto EXITLOOP;
                    case 'J':
                    manilha->inicioCuringa->ant->prox = manilha->mAtual;
                    manilha->mAtual->ant = manilha->inicioCuringa->ant;
                    manilha->inicioCuringa->ant = manilha->mAtual;
                    manilha->mAtual->prox = manilha->inicioCuringa;
                    goto EXITLOOP;
                }

            }

        }
                    
    EXITLOOP:
        
    }
    else
    {
        printf("\nestado 4!");
        
        NoManilha *tempManilha = corAtual;
        printf("\nCategoria: %c\n", corAtual->carta.categoria);
        printf("Num: %d\n", corAtual->carta.numero);
        corAtual->carta.categoria;
        if(carta == NULL){
            perror("Erro carta é NULL");
            exit(EXIT_FAILURE);
        }
            
        for(;;){
            tempManilha = tempManilha->prox;
            printf("\n1Categoria: %c\n", noManilha->carta.categoria);
            printf("Num: %d\n", noManilha->carta.numero);

            printf("\n2Categoria: %c\n", tempManilha->carta.categoria);
            printf("Num: %d\n", tempManilha->carta.numero);
            if( noManilha->carta.categoria != tempManilha->carta.categoria ||
                noManilha->carta.numero > tempManilha->carta.numero ||
                tempManilha == corAtual)
            {
                    tempManilha->ant->prox = noManilha;
                    noManilha->ant = tempManilha->ant;
                    tempManilha->ant = noManilha;
                    noManilha->prox = tempManilha;
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

        Carta carta = pegarCarta(jogo->bCompra);
        if(carta.categoria >= 13){
            srand(time(NULL));
            carta.categoria == "RGBY"[rand() % 4];
        }
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
        Carta carta = pegarCarta(baralho);

        if(&carta == NULL){
            perror("Erro: Carta do Baralho é NULL");
            exit(EXIT_FAILURE);
        }
        printf("\n3");
        adicionarNoMalinha(noJogador->manilha, &carta);
        printf("\n4");
    }
}

Carta *getCartaMesa(Jogo *jogo){
    if(!baralhoVazio(jogo->bMesa))
    return &(jogo->bMesa->cartas[jogo->bMesa->topo]);
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

Carta pegarCartaManilha(Manilha *manilha){
    printf("pegarCartaManilha Entrada");
    if (manilha->qtd == 0) {
        // Se a lista estiver vazia, retorne uma carta inválida
        Carta carta_vazia;
        carta_vazia.numero = -1;
        return carta_vazia;
    }

    Carta carta = manilha->mAtual->carta;
    NoManilha *tempManilha = manilha->mAtual;

    // Se só houver um nó na lista, resete a manilha
    if (manilha->qtd == 1) {
        free(tempManilha);
        manilha->mAtual = NULL;
    } else {
        // Atualize os ponteiros da manilha
        tempManilha->ant->prox = tempManilha->prox;
        tempManilha->prox->ant = tempManilha->ant;
        manilha->mAtual = tempManilha->prox;
        free(tempManilha);
    }

    manilha->qtd--;
    printf("pegarCartaManilha Saida");
    return carta;
}

Carta *enviarManilha(Manilha *manilha, Baralho *baralho) {
    if (baralho == NULL || baralhoVazio(baralho)) {
        perror("Erro Crítico: Baralho Vazio, não foi possível transferir %d Cartas para a manilha\n");
        exit(EXIT_FAILURE);
    }

        Carta carta = pegarCartaManilha(manilha);

        if(&carta == NULL){
            perror("Erro: Carta é NULL");
            exit(EXIT_FAILURE);
        }
        adicionarCarta(baralho, carta);
        return &baralho->cartas[baralho->topo];
}

char maiorQtdCor(Jogo *jogo) {
    Manilha *manilha = jogo->cicloJogadores->jAtual->manilha;
    int numCor[4] = {0}; // Inicializa com 0
    int maiorQtd = -1; // Inicializa com um valor menor que qualquer possível em numCor
    int maiorCor = 0;
    char cor[4] = "RGBY";
    
    do {
        if (manilha->mAtual->carta.categoria == 'J') {
            manilha->mAtual = manilha->mAtual->prox;
            continue;
        }
        
        char *posicao = strchr(cor, manilha->mAtual->carta.categoria);
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

int poderCarta(Carta *carta, Jogo *jogo) {
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

void alterarCorCarta(Jogo *jogo, Carta *carta){
    bool prox = false;
    char cor;
    system("cls");
    if(isPlayer(jogo) == false){
        srand(time(NULL));
        if((rand() % 10) <= 3){ //40% de chance de escolher uma cor aléatoria 
            printf("\nranddaw");
            jogo->bMesa->cartas[jogo->bMesa->topo].categoria = maiorQtdCor(jogo);
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
    exit(EXIT_FAILURE);
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

bool verificarComprarCarta(Jogo *jogo, int compra){
    
    system("cls");
    for(;compra > 0;compra--){
        Carta cartaComprada = pegarCartaCompra(getBaralhoMesa(jogo), getBaralhoCompra(jogo));
        adicionarNoMalinha(jogo->cicloJogadores->jAtual->manilha, &cartaComprada);
        printf("\nCarta Comprada[%d]\n", compra);
        printCarta(jogo->cicloJogadores->jAtual->manilha);
    }

    if(comprar4PoderSkip(jogo))
    return true;
        
return false;
}

int selecionarCarta(char tecla, Jogo *jogo) {
  switch (tecla) {
  case 'A': case 'a':
    jogo->cicloJogadores->jAtual->manilha->mAtual = jogo->cicloJogadores->jAtual->manilha->mAtual->ant;
    printf("\n\nMesa: ");
    printf("Numero: %d ", jogo->bMesa->cartas[jogo->bMesa->topo].numero);
    printf("Cor: %c \n", jogo->bMesa->cartas[jogo->bMesa->topo].categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.categoria);
    return -1;
  case 'D': case 'd':
    jogo->cicloJogadores->jAtual->manilha->mAtual = jogo->cicloJogadores->jAtual->manilha->mAtual->prox;
    printf("\n\nMesa: ");
    printf("Numero: %d ", jogo->bMesa->cartas[jogo->bMesa->topo].numero);
    printf("Cor: %c \n", jogo->bMesa->cartas[jogo->bMesa->topo].categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.categoria);
    return -1;
  case 'W': case 'w':
    Carta tempCarta = jogo->bMesa->cartas[jogo->bMesa->topo];
    printf("\n\nMesa: ");
    printf("Numero: %d ", tempCarta.numero);
    printf("Cor: %c \n", tempCarta.categoria);
    
    printf("\nManilha: ");
    printf("Numero: %d ", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.numero);
    printf("Cor: %c \n\n", jogo->cicloJogadores->jAtual->manilha->mAtual->carta.categoria);
    if(jogadaValida(&(jogo->cicloJogadores->jAtual->manilha->mAtual->carta),
                    &(jogo->bMesa->cartas[jogo->bMesa->topo]))) 
    {
      Carta *carta = enviarManilha(jogo->cicloJogadores->jAtual->manilha, jogo->bMesa);
      return poderCarta(carta, jogo);
    }
    printf("Jogada Inválida");
    return -1;

    break;
  case 'S': case 's':
    void **ptrs = cartasJogaveis(topoBaralho(jogo->bMesa), jogo->cicloJogadores->jAtual->manilha);
    int *cQtd = (int *)ptrs[0];
    if(*cQtd <= 0){

        START:
        Carta carta = comprarCarta(jogo);
        if(carta.numero != -1);
        if(!jogadaValida(&carta, &jogo->bMesa->cartas[jogo->bMesa->topo])){
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

bool comprar4PoderSkip(Jogo *jogo){
    if(getCartaMesa(jogo)->numero == 14)
    {
        proximoNoJogador(jogo);
    }
        return true;
    return false;
}

void abastercerBaralho(Baralho *baralhoReceptor, Baralho *baralhoDoador){
    Carta carta;
    for(; baralhoDoador->topo > 0;){
        printf("PEGOU CARTA ABSTERCER!!!!!!!!!!!!!!!!!!!!!");
        carta = pegarCarta(baralhoDoador);
        adicionarCarta(baralhoReceptor, carta);

    }
    printf("saiu");
}

Carta pegarCartaCompra(Baralho *baralhoMesa, Baralho *baralhoCompra){
        printf("\npegarCartaCompra");
        Carta carta = pegarCarta(baralhoCompra);

        if(carta.numero <= -1 && baralhoMesa->topo > 0){
            abastercerBaralho(baralhoCompra, baralhoMesa);
            carta = pegarCarta(baralhoCompra);
        }

        printf("\nNúmero: %d", carta.numero);
        printf("\nCor %c\n", carta.categoria);

        return carta;
    
}

bool comprarCartaBot(Jogo *jogo){
    for(;;){
        printf("Sem Carta Necessaria");
        Carta cartaComprada = comprarCarta(jogo);        
        if(cartaComprada.numero == -1)
        {
            printf("Baralho da Mesa e Baralha compra vazios!\n Passando a vez!");
            return false;
        }
        if(jogadaValida(&cartaComprada, getCartaMesa(jogo))){
            return true;
        }
    }
}


Carta comprarCarta(Jogo *jogo){
    
    Manilha *manilha = jogo->cicloJogadores->jAtual->manilha;
    Baralho *baralhoMesa = jogo->bMesa;
    Baralho *baralhoCompra = jogo->bCompra;
    printf("\ncomprarCarta");
    Carta carta = pegarCartaCompra(baralhoMesa, baralhoCompra);
    if(carta.numero == -1 || &carta.categoria == NULL){
        printf("comprarCarta return NULL");
        exit(EXIT_FAILURE);
    }
    adicionarNoMalinha(manilha, &carta);

    return carta;
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
    NoManilha *tempMani = atual->mAtual;
    printf("\n\n\nPega Visão\n\n\n\n\n\n\n");
    do{
        if(&atual->mAtual->carta == NULL){
            perror("Erro: carta NULL");
            exit(EXIT_FAILURE);
        }

        if(jogadaValida(&(tempMani->carta), topo)){
            
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

    printf("Carta:\ncategoria: %c\n", manilha->mAtual->carta.categoria);
    printf("numero: %d\n\n", manilha->mAtual->carta.numero);
}
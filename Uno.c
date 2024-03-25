#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Uno.h"

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
    struct manilha *prox, *ant;
} Manilha;

typedef struct jogador{
char nome;
unsigned int vitorias;
struct *manilha;
int qtd_cartas;
}

//
typedef struct baralho {
    Carta carta[BARALHO_SIZE];
    int topo;
} Baralho;

// Função para inicializar o baralho
void inicializarBaralho(Baralho *baralho) {
    if(baralho->topo != 0 || baralho->carta != NULL){
        printf("Erro: erro ao inicializar o baralho (Obs.: baralho já possui dados ou foi inicializado)");
        return;
    }
    baralho->topo = -1; // Define o topo como -1 para indicar que o baralho está vazio
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
    Carta cartaVazia = {-1, ""}; // Carta vazia para indicar erro
    if (baralhoVazio(baralho)) {
        printf("Erro: o baralho está vazio\n");
        return cartaVazia; // Retorna uma carta vazia indicando erro
    } else {
        Carta carta = baralho->carta[baralho->topo]; // Obtém a carta do topo
        baralho->topo--; // Decrementa o topo
        return carta; // Retorna a carta removida
    }
}
//

void listarBaralho(Baralho *cartas){
    
    for(int i = 0; i < cartas->topo; i++)
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

void distribuir_baralho(Baralho *baralho, Manilha **manilha, int quant) {
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

void embaralhar_matriz(char matrix[2][BARALHO_SIZE]) {
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

Baralho* criar_baralho() {
    FILE *file;
    file = fopen("baralho.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    char tempCartas[2][BARALHO_SIZE];
    char carta[10];
    int i = 0;
    while (fgets(carta, 10, file) != NULL) {
        char *token = strtok(carta, "-");
        tempCartas[0][i] = token[0];
        token = strtok(NULL, "-");
        tempCartas[1][i] = atoi(token);
        i++;
    }

    fclose(file);

    embaralhar_matriz(tempCartas);

    Baralho* baralho_principal = (Baralho*)malloc(sizeof(Baralho));
    if (baralho_principal == NULL) {
        printf("Erro: ao alocar memória para o baralho!\n");
        return NULL;
    }

    baralho_principal->topo = -1;
    for (int i = 0; i < BARALHO_SIZE; i++) {
        baralho_principal->topo++;
        baralho_principal->carta[baralho_principal->topo].categoria = tempCartas[0][i];
        baralho_principal->carta[baralho_principal->topo].numero = tempCartas[1][i];
    }

    return baralho_principal;
}



/*void embaralhar(baralho *cartas)
{

    int num_cartas = 0;
    baralho *carta_atual = cartas;
    while (carta_atual != NULL)
    {
        num_cartas++;
        carta_atual = carta_atual->prox;
    }


    for (int i = num_cartas - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        baralho *carta_i = cartas;
        for (int k = 0; k < i; k++)
        {
            carta_i = carta_i->prox;
        }
        baralho *carta_j = cartas;
        for (int k = 0; k < j; k++)
        {
            carta_j = carta_j->prox;
        }

        int temp_numero = carta_i->numero;
        char temp_categoria = carta_i->categoria;
        carta_i->numero = carta_j->numero;
        carta_i->categoria = carta_j->categoria;
        carta_j->numero = temp_numero;
        carta_j->categoria = temp_categoria;
    }
}*/

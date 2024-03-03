#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct manilha
{
    int numero;
    char categoria;
    struct manilha *prox, *ant;
} manilha;

typedef struct baralho
{
    int numero;
    char categoria;
    struct baralho *prox;
} baralho;

void embaralhar(baralho *cartas);

int main()
{
    
    baralho *baralho_principal = NULL;
    baralho *carta_atual = NULL;
    srand(time(NULL));

    
    for (int i = 0; i < 10; i++)
    {
        carta_atual = (baralho *)malloc(sizeof(baralho));
        carta_atual->numero = i + 1;
        carta_atual->categoria = 'A' + i % 4;
        carta_atual->prox = baralho_principal;
        baralho_principal = carta_atual;
    }

    
    embaralhar(baralho_principal);

    
    printf("Cartas embaralhadas:\n");
    carta_atual = baralho_principal;
    while (carta_atual != NULL)
    {
        printf("Número: %d, Categoria: %c\n", carta_atual->numero, carta_atual->categoria);
        carta_atual = carta_atual->prox;
    }

    
    carta_atual = baralho_principal;
    while (carta_atual != NULL)
    {
        baralho *temp = carta_atual;
        carta_atual = carta_atual->prox;
        free(temp);
    }

    return 0;
}

void embaralhar(baralho *cartas)
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
}

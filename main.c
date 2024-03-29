#include <stdio.h>
#include <stdlib.h>

#include "Uno.h"

int main()
{

    Baralho* cartas = criar_baralho();
    listarBaralho(cartas);
    Manilha* p1 = inicializarManilha();
    printf("tesrt");
    distribuir_baralho(cartas, &p1, 14);
    system("pause");
    printf("\nprox\n");
    listarManilha(p1);
    /*
    printf("Cartas: \n");
    listarBaralho(cartas);
    Baralho* mesa = criarMesa();
    printf("Mesa: \n");
    listarBaralho(mesa);
    reembaralhar(mesa, cartas);
    printf("Cartas: \n");
    listarBaralho(cartas);
    printf("Mesa: \n");
    listarBaralho(mesa);
    */

    return 0;
}

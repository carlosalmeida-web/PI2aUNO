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

    return 0;
}

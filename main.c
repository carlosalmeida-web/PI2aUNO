#include <stdio.h>

#include "Uno.h"

int main()
{

    Baralho* cartas = criar_baralho();
    listarBaralho(cartas);
    Manilha* p1;
    distribuir_baralho(cartas, &p1, 10);
    printf("\nprox\n");
    listarManilha(p1);

    return 0;
}

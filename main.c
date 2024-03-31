#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Uno.h"

int main()
{
    int botQuant = 3;
    int cartasInicial = 15;
    
    Manilha* ganhador = NULL;
    Ciclo* ciclo = criarCiclo();
    Jogo* jogo = criarJogo(ciclo);
    Baralho* cartas = gerarBaralho();
    Manilha* player = inicializarManilha();
    adicionarCiclo(jogo, player, true);
    distribuirBaralho(cartas, &player, cartasInicial);

    Manilha* bot[botQuant]; 
    
    
    for(; botQuant-1 > 0; botQuant--){
        
        printf("2");
        bot[botQuant] = inicializarManilha();
        printf("1");
        distribuirBaralho(cartas, &(bot[botQuant]), cartasInicial);
        adicionarCiclo(jogo, bot[botQuant], false);
        
    }
    do{
        printf("do\n");

        if(isPlayer(jogo)){
            printf("Certo :D\n");
        }else if(!isPlayer(jogo)){
            printf("SUS\n");
        }else{
            printf("Erro: tipo de Player não indentificado!\n");
        }

        proximoCiclo(jogo);
    }while(ganhador == NULL);

/*
    listarBaralho(cartas);
    printf("tesrt");
    system("pause");
    printf("\nprox\n");
    listarManilha(p1);
    
    printf("Cartas: \n");
    listarBaralho(cartas);
    Baralho* mesa = criarBaralho();
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Uno.h"

int main()
{
    int botQuant = 3;
    int cartasInicial = 15;
    Manilha *ganhador = NULL;
    printf("2");

    Ciclo* ciclo = criarCiclo();
    Jogo* jogo = criarJogo(ciclo);
    printf("2");
    
    Baralho* cartas = gerarBaralho();
    
    Manilha* player = inicializarManilha();
    printf("2");

    adicionarCiclo(jogo, player, true);
    distribuirBaralho(cartas, &player, cartasInicial);
    printf("2");

    Manilha* bot[botQuant]; 
    
    
    for (; botQuant > 0; botQuant--) {
    printf("2");
    bot[botQuant - 1] = inicializarManilha();
    printf("1");
    distribuirBaralho(cartas, &(bot[botQuant - 1]), cartasInicial);
    adicionarCiclo(jogo, bot[botQuant - 1], false);
    }

    do{
        printf("teste");

        listarCiclo(jogo);
        /* Exemplo
        void **ptrs = cartasJogaveis(topoBaralho(cartas), player);

        int *brabo = (int *)ptrs[0];
        Manilha *rato = (Manilha *)ptrs[1];
        Manilha *segundo = (Manilha *)ptrs[2];
        Manilha *terceiro = (Manilha *)ptrs[3];

        printf("brabo: %d", *brabo);
        printCarta(rato);
        printCarta(segundo);
        printCarta(terceiro);
        */
        printf("teste");

        if(isPlayer(jogo) == false){
                    printf("teste1");

            selecionarCarta(getchar(), jogo);
            printf("Certo :D\n");
        }else if(isPlayer(jogo) == true){
                    printf("teste2");

            void **ptrs = cartasJogaveis(topoBaralho(cartas), player);
            printf("bot!\n");
            int *cQtd = (int *)ptrs[0];
                        printf("bot!\n");

            srand(time(NULL));
                        printf("bot!\n");

            *cQtd = (rand() % (*cQtd-1))+1;
                        printf("bot!\n");


            Manilha *jogada = (Manilha *)ptrs[*cQtd];
            Carta *teste = enviarManilha(jogada, cartas);
            poderCarta(teste, jogo);
                        printf("bot!\n");

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
*/  printf("reste\n");

    return 0;
}

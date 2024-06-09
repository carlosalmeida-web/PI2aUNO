#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "pthread.h"
#include "Uno.h"

int main()
{

    int botQuant = 3;
    int cartasInicial = 15;
    bool ganhador = false;
    Jogo* jogo = criarJogo();
    
    Baralho *cartas = getBaralhoCompra(jogo);
    
    NoJogador *player = criarNoJogador(true);
    adicionarNoJogador(jogo, player, true);
    distribuirBaralho(cartas, player, cartasInicial);
    listarManilha(getManilha(jogo));

    //NoJogador* bot[botQuant]; 
    
    
    for (; botQuant > 0; botQuant--) {
    NoJogador* bot = criarNoJogador(false);

    distribuirBaralho(cartas, bot, cartasInicial);
    adicionarNoJogador(jogo, bot, false);
    if(isPlayer(jogo))
        printf("\nisPlayer\n");
    }

    
    int Compra = 0;
    
    pthread_t threadPlayer;
    pthread_t unoState;

    pthread_create(&threadPlayer, NULL, playerUnoThread, player);

    do{
        proximoNoJogador(jogo);
        listarNoJogador(jogo);
        
        checarLista(jogo);
        if(isPlayer(jogo)){

            if(Compra > 0 && verificarComprarCarta(jogo, &Compra))
            {
                continue;
            }
            
            char comando = '\0';
            char aceitaveis[8] = {'a','A','s','S','d','D','w','W'};
            int exitLoop = -1;
            do{
                printf("Escolha sua acao entre:\n a - Esquerda\n d - Direita\n s - Comprar(Se Possivel)\n w - Jogar Carta Destacada(Se Possivel)\n");
                comando = inputsAceitaveis(aceitaveis, sizeof(aceitaveis) / sizeof(aceitaveis[0]), player); 
                //TODO: substituir por switch
                if(comando == 'a' || comando == 'A' ||
                   comando == 's' || comando == 'S' ||
                   comando == 'd' || comando == 'D' ||
                   comando == 'w' || comando == 'W'){
                    exitLoop = selecionarCarta(comando, jogo);
                }

            }while(exitLoop == -1);
            Compra = exitLoop;
            //selecionarCarta(getchar(), jogo);
            printf("Certo :D\n");
            
        }else{
            if(Compra > 0 && verificarComprarCarta(jogo, &Compra))
            {
                continue;
            }
            
            void **ptrs = cartasJogaveis(topoBaralho(getBaralhoMesa(jogo)), getManilha(jogo));
            int *cQtd = (int *)ptrs[0];

            if(*cQtd > 0){
            
            srand(time(NULL));
            
            if(*cQtd > 1){
                *cQtd = (rand() % (*cQtd-1))+1;
            }else{
                *cQtd = 1;
            }
            
            Manilha *jogada = (Manilha *)ptrs[*cQtd];
            NoCarta *teste = enviarManilha(jogada, getBaralhoMesa(jogo));
            Compra = poderCarta(teste, jogo);
            
            }else{
                
                bool skip = comprarCartaBot(jogo);
                if(skip == false)
                {
                Manilha *jogada = getManilha(jogo);
                NoCarta *teste = enviarManilha(jogada, getBaralhoMesa(jogo));
                Compra = poderCarta(teste, jogo);
                }                
            }

        }
        ganhador = manilhaVazia(jogo);
        printf("\nProximo Jogador\n"); 
    }while(!ganhador);
    printf("reste\n");

    return 0;
}

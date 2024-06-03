#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

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
    do{
        proximoNoJogador(jogo);
        listarNoJogador(jogo);
        
        checarLista(jogo);
        if(isPlayer(jogo)){

            if(Compra > 0 && verificarComprarCarta(jogo, &Compra))
            {
                continue;
            }
            
            char comando = 'n';
            int exitLoop = -1;
            do{
            
                printf("Escolha sua acao entre:\n a - Esquerda\n d - Direita\n s - Comprar(Se Possivel)\n w - Jogar Carta Destacada(Se Possivel)\n");
                fflush(stdin);
                comando = _getch(); 
                if(comando == 'a' || comando == 's' || comando == 'd' || comando == 'w'){
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

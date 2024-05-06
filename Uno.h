#ifndef UNO_H
#define UNO_H 1

#define BARALHO_SIZE 108

typedef struct manilha Manilha;
typedef struct baralho Baralho;
typedef struct carta Carta;
typedef struct ciclo Ciclo;
typedef struct perfil Perfil;
typedef struct jogo Jogo;

Ciclo *criarCiclo();
Jogo *criarJogo(Ciclo *ciclo);
Baralho *gerarBaralho();
void inicializarBaralho(Baralho *baralho);
void adicionarCiclo(Jogo *jogo, Manilha *manilha, bool _isPlayer);
int baralhoVazio(Baralho *baralho);
int baralhoCheio(Baralho *baralho);
void proximoCiclo(Jogo *jogo);
void adicionarCarta(Baralho *baralho, Carta carta);
Carta pegarCarta(Baralho *baralho);
void listarCiclo(Jogo *jogo);
void listarBaralho(Baralho *cartas);
void listarManilha(Manilha *cartas);
Manilha *inicializarManilha();
void distribuirBaralho(Baralho *baralho, Manilha **manilha, int quant);
void reembaralhar(Baralho *baralho, Baralho *mesa);
Baralho *criarBaralho();
void embaralharMatriz(char matrix[2][BARALHO_SIZE]);
void **cartasJogaveis(Carta *topo, Manilha *atual);
Carta *topoBaralho(Baralho *baralho);
bool jogadaValida(Carta *pCarta, Carta *mCarta);
bool selecionarCarta(char tecla, Jogo *jogo);
bool isPlayer(Jogo *jogo);
int poderCarta(Carta *carta, Jogo *jogo);
Carta *enviarManilha(Manilha *manilha, Baralho *baralho);
void printCarta(Manilha *manilha);
Manilha *getManilha(Jogo *jogo);



#endif // UNO_H
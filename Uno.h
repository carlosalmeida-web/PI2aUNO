#ifndef UNO_H
#define UNO_H 1

#define BARALHO_SIZE 108

typedef struct manilha Manilha;
typedef struct noManilha NoManilha;
typedef struct noJogador NoJogador;
typedef struct baralho Baralho;
typedef struct carta Carta;
typedef struct perfil Perfil;
typedef struct jogo Jogo;
typedef struct listaJogadorCircular ListaJogadorCircular;

int baralhoVazio(Baralho *baralho);
int baralhoCheio(Baralho *baralho);
void adicionarCarta(Baralho *baralho, Carta carta);
Carta pegarCarta(Baralho *baralho);
void listarBaralho(Baralho *cartas);
void listarManilha(Manilha *cartas);
Manilha *criarManilha();
NoManilha *slotOrdemManilha(Manilha *manilha, char cor, bool reservar);
void adicionarNoMalinha(Manilha *manilha, Carta *carta);
Jogo *criarJogo(NoJogador *noJogador);
void proximoNoJogador(Jogo *jogo);
bool isPlayer(Jogo *jogo);
void distribuirBaralho(Baralho *baralho, Manilha *manilha, int quant);
Manilha *getManilha(Jogo *jogo);
Carta *enviarManilha(Manilha *manilha, Baralho *baralho);
char maiorQtdCor(Jogo *jogo);
int poderCarta(Carta *carta, Jogo *jogo);
void listarNoJogador(Jogo *jogo);
void adicionarNoJogador(Jogo *jogo, Manilha *manilha, bool _isPlayer);
NoJogador *criarNoJogador();
void embaralharMatriz(char matrix[2][BARALHO_SIZE]);
Baralho* gerarBaralho();
void reembaralhar(Baralho *baralho, Baralho *mesa);
Carta *topoBaralho(Baralho *baralho);
bool jogadaValida(Carta *pCarta, Carta *mCarta);
bool selecionarCarta(char tecla, Jogo *jogo);
void **cartasJogaveis(Carta *topo, Manilha *atual);
void printCarta(Manilha *manilha);

#endif // UNO_H
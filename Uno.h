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

bool comprar4PoderSkip(Jogo *jogo);
void checarLista(Jogo *jogo);
bool verificarComprarCarta(Jogo *jogo, int compra);
Carta pegarCartaCompra(Baralho *baralhoMesa, Baralho *baralhoCompra);
Baralho *getBaralhoMesa(Jogo *jogo);
bool comprarCartaBot(Jogo *jogo);
Baralho *getBaralhoCompra(Jogo *jogo);
int baralhoVazio(Baralho *baralho);
void alterarCorCarta(Jogo *jogo, Carta *carta);
bool manilhaVazia(Jogo *jogo);
int baralhoCheio(Baralho *baralho);
void adicionarCarta(Baralho *baralho, Carta carta);
Carta pegarCarta(Baralho *baralho);
void listarBaralho(Baralho *cartas);
void listarManilha(Manilha *cartas);
Manilha *criarManilha();
ListaJogadorCircular *criarCiclo();
NoManilha *slotOrdemManilha(Manilha *manilha, char cor);
void adicionarNoMalinha(Manilha *manilha, Carta *carta);
Jogo *criarJogo();
void proximoNoJogador(Jogo *jogo);
bool isPlayer(Jogo *jogo);
void distribuirBaralho(Baralho *baralho, NoJogador *noJogador, int quant);
Manilha *getManilha(Jogo *jogo);
Carta *enviarManilha(Manilha *manilha, Baralho *baralho);
char maiorQtdCor(Jogo *jogo);
int poderCarta(Carta *carta, Jogo *jogo);
void listarNoJogador(Jogo *jogo);
void adicionarNoJogador(Jogo *jogo, NoJogador *noJogador, bool _isPlayer);
NoJogador *criarNoJogador(bool _isPlayer);
void embaralharMatriz(char matrix[2][BARALHO_SIZE]);
Baralho* gerarBaralho();
void reembaralhar(Baralho *baralho, Baralho *mesa);
Carta *topoBaralho(Baralho *baralho);
bool jogadaValida(Carta *pCarta, Carta *mCarta);
int selecionarCarta(char tecla, Jogo *jogo);
void **cartasJogaveis(Carta *topo, Manilha *atual);
Carta *getCartaMesa(Jogo *jogo);
void printCarta(Manilha *manilha);
Carta comprarCarta(Jogo *jogo);

#endif // UNO_H
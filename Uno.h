#ifndef UNO_H
#define UNO_H 1

#define BARALHO_SIZE 108

typedef struct manilha Manilha;
typedef struct noCarta NoCarta;
typedef struct noJogador NoJogador;
typedef struct baralho Baralho;
typedef struct noCarta NoCarta;
typedef struct perfil Perfil;
typedef struct jogo Jogo;
typedef struct listaJogadorCircular ListaJogadorCircular;

void checarLista(Jogo *jogo);
bool verificarComprarCarta(Jogo *jogo, int *compra);
NoCarta *pegarCartaCompra(Baralho *baralhoMesa, Baralho *baralhoCompra);
Baralho *getBaralhoMesa(Jogo *jogo);
bool comprarCartaBot(Jogo *jogo);
void *playerUnoThread(void *jogador);
void *unoThread(void *jogador, void *jogoAtual);
char inputsAceitaveis(char *vectorInput, size_t size, NoJogador *noJogador);
NoJogador *getNoPlayer(NoJogador *noJogador);
Baralho *getBaralhoCompra(Jogo *jogo);
int baralhoVazio(Baralho *baralho);
void alterarCorCarta(Jogo *jogo, NoCarta *noCarta);
bool manilhaVazia(Jogo *jogo);
int baralhoCheio(Baralho *baralho);
void adicionarCarta(Baralho *baralho, NoCarta *noCarta);
NoCarta *pegarCarta(Baralho *baralho);
void listarBaralho(Baralho *cartas);
void listarManilha(Manilha *cartas);
Manilha *criarManilha();
ListaJogadorCircular *criarCiclo();
NoCarta *slotOrdemManilha(Manilha *manilha, char cor);
void adicionarNoMalinha(Manilha *manilha, NoCarta *noCarta);
Jogo *criarJogo();
void proximoNoJogador(Jogo *jogo);
bool isPlayer(Jogo *jogo);
void distribuirBaralho(Baralho *baralho, NoJogador *noJogador, int quant);
Manilha *getManilha(Jogo *jogo);
NoCarta *enviarManilha(Manilha *manilha, Baralho *baralho);
char maiorQtdCor(Jogo *jogo);
int poderCarta(NoCarta *noCarta, Jogo *jogo);
void listarNoJogador(Jogo *jogo);
void adicionarNoJogador(Jogo *jogo, NoJogador *noJogador, bool _isPlayer);
NoJogador *criarNoJogador(bool _isPlayer);
void embaralharMatriz(char matrix[2][BARALHO_SIZE]);
Baralho* gerarBaralho();
void reembaralhar(Baralho *baralho, Baralho *mesa);
NoCarta *topoBaralho(Baralho *baralho);
bool jogadaValida(NoCarta *pCarta, NoCarta *mCarta);
int selecionarCarta(char tecla, Jogo *jogo);
void **cartasJogaveis(NoCarta *topo, Manilha *atual);
NoCarta *getCartaMesa(Jogo *jogo);
void printCarta(Manilha *manilha);
NoCarta *comprarCarta(Jogo *jogo);

#endif // UNO_H
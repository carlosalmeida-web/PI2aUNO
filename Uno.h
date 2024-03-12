#ifndef UNO_H
#define UNO_H 1

#define BARALHO_SIZE 108

typedef struct manilha Manilha;
typedef struct baralho Baralho;
typedef struct carta Carta;

Baralho *criar_baralho();
void inicializarBaralho(Baralho *baralho);
int baralhoVazio(Baralho *baralho);
int baralhoCheio(Baralho *baralho);
void adicionarCarta(Baralho *baralho, Carta carta);
Carta pegarCarta(Baralho *baralho);
void listarBaralho(Baralho *cartas);
void listarManilha(Manilha *cartas);
void distribuir_baralho(Baralho *baralho, Manilha **manilha, int quant);
void embaralhar(Baralho *cartas);
void embaralhar_matriz(char matrix[2][BARALHO_SIZE]);


#endif // UNO_H
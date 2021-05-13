#ifndef BTREE_H
#define BTREE_H
#include <stdbool.h>
#include "estatisticas.h"

#define M 2
#define MM 2*M

typedef struct TipoRegistro{
    int key;
    long int iData;
    char sData[500];
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];

    int intPointer[MM + 1];
    int position;
} TipoPagina;

TipoApontador criaPagina();
void liberaPagina(TipoApontador pag);
TipoRegistro* constructorTipoRegistro();
void freeTipoRegistro(TipoRegistro* reg);
int sizeofTipoRegistro();
int sizeofBTree();

int getChave(TipoRegistro* regs);
long int getDadoInteiro(TipoRegistro* regs);
char* getDadoString(TipoRegistro* regs);

void setChave(TipoRegistro* reg, int key);
void setDadoInteiro(TipoRegistro* reg, long int iData);
void setDadoString(TipoRegistro* reg, char* sData);

void Inicializa (TipoApontador Arvore);

void pesquisa(TipoRegistro* x, TipoApontador Ap, Est* est);
void searchBTree(TipoRegistro* reg, FILE* input, TipoPagina* bTree, Est* est);
void Imprime(TipoApontador arvore);
void insereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, Est* est);
void ins(TipoRegistro Reg, TipoApontador Ap, short* cresceu, TipoRegistro* RegRetorno, TipoApontador* ApRetorno, Est* est);
void insere(TipoRegistro Reg, TipoApontador *Ap, Est* est);

#endif
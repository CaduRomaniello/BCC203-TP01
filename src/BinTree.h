#ifndef BINTREE_H
#define BINTREE_H
#include "estatisticas.h"

typedef struct titem{
    int key;
    long int iData;
    char sData[500];
} TItem;

typedef struct No {
    TItem item ;
    struct No *pEsq, *pDir;
    
    int posicao;
    int iEsq, iDir;
}TNo;

// Construtores
TNo* criaTNo();
TItem* criaTItem();
void liberaTNo(TNo* t);
void liberaTItem(TItem* t);

// Get
int getBinKey(TNo* t);
long int getBinIData(TNo* t);
char* getBinSData(TNo* t);
int getBinIEsq(TNo* t);
int getBinIDir(TNo* t);
int getBinPosicao(TNo* t);

// Set
void setBinKey(TNo* t, int key);
void setBinIData(TNo* t, long int iData);
void setBinSData(TNo* t, char* sData);
void setBinIEsq(TNo* t, int iEsq);
void setBinIDir(TNo* t, int iDir);
void setBinPosicao(TNo* t, int posicao);
void setBinKeyItem(TItem* t, int key);
void setBinIDataItem(TItem* t, long int iData);
void setBinSDataItem(TItem* t, char* sData);

// Tree Methods
int FB (TNo* pRaiz, Est* est);
int Altura(TNo* pRaiz, Est* est);
void RSE(TNo** ppRaiz, Est* est);
void RSD (TNo** ppRaiz, Est* est);
int BalancaEsquerda(TNo** ppRaiz, Est* est);
int BalancaDireita(TNo** ppRaiz, Est* est);
int Balanceamento(TNo** ppRaiz, Est* est);
int Insere(TNo** ppRaiz, TItem * x, Est* est);
void searchBinaryTree(TNo* arvore, TItem* t, FILE* input, Est* est);

void printaArvoreBinaria(TNo* arvore);

#endif
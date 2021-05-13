#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BinTree.h"

TNo* criaTNo(){
    TNo* aux = malloc(sizeof(TNo));
    aux->posicao = -1;
    aux->iEsq = -1;    
    aux->iDir = -1;   
    aux->pEsq = NULL; 
    aux->pDir = NULL; 
    return aux;
}
TItem* criaTItem(){
    TItem* aux = malloc(sizeof(TItem));
    aux->iData = -1;
    return aux;
}
void liberaTNo(TNo* t){
    free(t);
}
void liberaTItem(TItem* t){
    free(t);
}

// Get
int getBinKey(TNo* t){
    return t->item.key;
}
long int getBinIData(TNo* t){
    return t->item.iData;
}
char* getBinSData(TNo* t){
    return t->item.sData;
}
int getBinIEsq(TNo* t){
    return t->iEsq;
}
int getBinIDir(TNo* t){
    return t->iDir;
}
int getBinPosicao(TNo* t){
    return t->posicao;
}

// Set
void setBinKey(TNo* t, int key){
    t->item.key = key;
}
void setBinIData(TNo* t, long int iData){
    t->item.iData = iData;
}
void setBinSData(TNo* t, char* sData){
    strcpy(t->item.sData, sData);
}
void setBinIEsq(TNo* t, int iEsq){
    t->iEsq = iEsq;
}
void setBinIDir(TNo* t, int iDir){
    t->iDir = iDir;
}
void setBinPosicao(TNo* t, int posicao){
    t->posicao = posicao;
}
void setBinKeyItem(TItem* t, int key){
    t->key = key;
}
void setBinIDataItem(TItem* t, long int iData){
    t->iData = iData;
}
void setBinSDataItem(TItem* t, char* sData){
    strcpy(t->sData, sData);
}

// Tree Methods
int FB (TNo* pRaiz, Est* est) {
    if (pRaiz == NULL)
    return 0;
    return Altura(pRaiz-> pEsq, est) - Altura(pRaiz-> pDir, est);
}

int Altura(TNo* pRaiz, Est* est) {
    int iEsq,iDir;
    if (pRaiz == NULL) return 0;
    iEsq = Altura(pRaiz-> pEsq, est);
    iDir = Altura(pRaiz-> pDir, est);
    if ( iEsq > iDir ){
        return iEsq + 1;
    }
    else {
        return iDir + 1;
    }
}

void RSE(TNo** ppRaiz, Est* est) {
    TNo *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux-> pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD (TNo** ppRaiz, Est* est) {
    TNo *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}



int BalancaEsquerda(TNo** ppRaiz, Est* est) {
    int fbe =  FB ( (*ppRaiz)->pEsq, est);
    if ( fbe >  0 ){
        RSD(ppRaiz, est);
        return 1;
    } else if (fbe <  0 ) { /* Rotação Dupla Direita */
        RSE( &((*ppRaiz)->pEsq), est);
        RSD( ppRaiz, est); /* &(*ppRaiz) */
        return 1;
    }
    
    return 0;
}

int BalancaDireita(TNo** ppRaiz, Est* est) {

    int fbd = FB((*ppRaiz)->pDir, est);
    if (fbd < 0) {
        RSE (ppRaiz, est);
        return 1;
    } else if (fbd > 0 ) { /* Rotação D upla Esquerda*/
        RSD (&((*ppRaiz)->pDir), est);
        RSE(ppRaiz, est); /* & (*ppRaiz) */
        return 1;
    }
    return 0;
}


int Balanceamento(TNo** ppRaiz, Est* est){
    int fb = FB(*ppRaiz, est);
    if (fb >  1)
        return BalancaEsquerda(ppRaiz, est);
    else if(fb < -1)
        return BalancaDireita(ppRaiz, est);
    else 
        return 0;
}

int Insere(TNo** ppRaiz, TItem * x, Est* est){
    incrementaComparacoesC(est);
    
    if (*ppRaiz == NULL){
        *ppRaiz = (TNo*) malloc(sizeof(TNo));
        (*ppRaiz)->item = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }
    else if ( (*ppRaiz)->item.key > x->key){
        if (Insere(&(*ppRaiz)->pEsq, x, est)){
            if (Balanceamento(ppRaiz, est)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else if ((*ppRaiz)->item.key < x->key){
        if (Insere(&(*ppRaiz)->pDir, x, est)){
            if (Balanceamento(ppRaiz, est)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0; /* valor jah presente */
    }

    return 0;
}

void printaArvoreBinaria(TNo* arvore){

    if (arvore == NULL) return;

    printf("----------- Item -----------\n");
    printf("| KEY    : %d\n", getBinKey(arvore));
    printf("| DATA I : %ld\n", getBinIData(arvore));
    printf("| DATA II: %s\n", getBinSData(arvore));
    printf("| IEsq   : %d\n", arvore->iEsq);
    printf("| IDir   : %d\n", arvore->iDir);
    printf("| Posicao: %d\n", arvore->posicao);
    printf("----------------------------\n\n");

    printaArvoreBinaria(arvore->pEsq);
    printaArvoreBinaria(arvore->pDir);
    
}

void searchBinaryTree(TNo* arvore, TItem* t, FILE* input, Est* est){
    if (arvore->posicao == -1){
        return;
    }
    else{
        incrementaComparacoesP(est);
        if (arvore->item.key == t->key){
            t->iData = arvore->item.iData;
            strcpy(t->sData, arvore->item.sData);
            return;
        }
        else if(arvore->item.key > t->key){
            if (VERBOSE) {
                printf("%d ", arvore->item.key);
            }
            if (arvore->iEsq != -1){
                fseek(input, arvore->iEsq * sizeof(TNo), SEEK_SET);
                fread(arvore, sizeof(TNo), 1, input);

                incrementaFseekP(est);
                incrementaFreadP(est);

                searchBinaryTree(arvore, t, input, est);
            }
            else{
                return;
            }
        }
        else{
            if (VERBOSE) {
                printf("%d ", arvore->item.key);
            }
            if (arvore->iDir != -1){
                fseek(input, arvore->iDir * sizeof(TNo), SEEK_SET);
                fread(arvore, sizeof(TNo), 1, input);
                
                incrementaFseekP(est);
                incrementaFreadP(est);

                searchBinaryTree(arvore, t, input, est);
            }
            else{
                return;
            }
        }
    }

}
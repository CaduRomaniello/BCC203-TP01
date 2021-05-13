#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "BTree.h"
#include "estatisticas.h"

typedef struct TipoPagina* TipoApontador;

// Construtores
TipoApontador criaPagina(){
    TipoApontador pag = (TipoPagina*) malloc(sizeof(TipoPagina));
    return pag;
}

void liberaPagina(TipoApontador pag){
    if (pag == NULL){
        return;
    }
    else{
        for (int i = 0; i < pag->n; i++){
            liberaPagina(pag->p[i]);
        }
        free(pag);
    }
}

TipoRegistro* constructorTipoRegistro(){
    TipoRegistro* reg = (TipoRegistro*) malloc(sizeof(TipoRegistro));

    if (reg == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }

    reg->key = -1;
    reg->iData = -1;
    strcpy(reg->sData, "");

    return reg;
}

void freeTipoRegistro(TipoRegistro* reg){
    free(reg);
}

// Gets
int sizeofTipoRegistro(){
    return sizeof(TipoRegistro);
}

int sizeofBTree(){
    return sizeof(TipoPagina);
}

int getChave(TipoRegistro* regs){
    return regs->key;
}

long int getDadoInteiro(TipoRegistro* regs){
    return regs->iData;
}

char* getDadoString(TipoRegistro* regs){
    return regs->sData;
}

// Sets
void setChave(TipoRegistro* reg, int key){
    reg->key = key;
}

void setDadoInteiro(TipoRegistro* reg, long int iData){
    reg->iData = iData;
}

void setDadoString(TipoRegistro* reg, char* sData){
    strcpy(reg->sData, sData);
}

/**
 * Inicializa uma árvore B
*/
void Inicializa (TipoApontador Arvore)
{
    Arvore = NULL;
}

/**
 * Pesquisa um item em uma árvore B interna
*/
void pesquisa(TipoRegistro* x, TipoApontador Ap, Est* est){
    long i = 1;
    if (Ap == NULL){
        return;
    }

    while(i < Ap->n && x->key > Ap->r[i-1].key) i++;
    if (x->key == Ap->r[i-1].key){
        *x = Ap->r[i-1];

        printf("----------- Item -----------\n");
        printf("| KEY    : %d\n", getChave(x));
        printf("| DATA I : %ld\n", getDadoInteiro(x));
        printf("| DATA II: %s\n", getDadoString(x));
        printf("----------------------------\n\n");
        return;
    }
    if (x->key < Ap->r[i-1].key){
        pesquisa(x, Ap->p[i-1], est);
    }
    else{
        pesquisa(x, Ap->p[i], est);
    }
}

/**
 * Pesquisa um item em uma árvore B externa
*/
void searchBTree(TipoRegistro* reg, FILE* input, TipoPagina* bTree, Est* est){

    int i = 1;

    while(i < bTree->n && reg->key > bTree->r[i - 1].key){
        i++;
        incrementaComparacoesP(est);
    }

    incrementaComparacoesP(est);
    if (reg->key == bTree->r[i - 1].key){
        *reg = bTree->r[i - 1];
        return;
    } else{
        if (VERBOSE){
            printf("%d ", bTree->r[i - 1].key);
        }
    }

    if (bTree->intPointer[0] == -1) return;

    incrementaComparacoesP(est);
    if (reg->key < bTree->r[i - 1].key){
        fseek(input, bTree->intPointer[i - 1] * sizeofBTree(), SEEK_SET);
        fread(bTree, sizeofBTree(), 1, input);

        incrementaFseekP(est);
        incrementaFreadP(est);

        searchBTree(reg, input, bTree, est);
    }
    else{
        fseek(input, bTree->intPointer[i] * sizeofBTree(), SEEK_SET);
        fread(bTree, sizeofBTree(), 1, input);
        
        incrementaFseekP(est);
        incrementaFreadP(est);
        
        searchBTree(reg, input, bTree, est);
    }

}

/**
 * Imprime uma árvore B interna
*/
void Imprime(TipoApontador arvore){
    
    if (arvore == NULL) return;

    if (arvore->p[0] == NULL){
        for (int i = 0; i < arvore->n; i++){
            printf("%d ", arvore->r[i].key);
        }
        puts("");
    }
    else{
        for (int i = 0; i <= arvore->n; i++){
            Imprime(arvore->p[i]);
        }
        for (int i = 0; i < arvore->n; i++){
            printf("%d ", arvore->r[i].key);
        }
        puts("");
    }

}

/**
 * Insere um item em uma página da árvore B
*/
void insereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, Est* est){
    short naoAchouPosicao;
    int k;
    k = Ap->n;
    naoAchouPosicao = (k > 0);
   
    while(naoAchouPosicao){
        incrementaComparacoesC(est);
        if (Reg.key >= Ap->r[k-1].key){
            naoAchouPosicao = false;
            break;
        }

        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        
        if(k < 1) naoAchouPosicao = false;
    }
   
    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

/**
 * Controla a inserção dos itens em uma árvore B
*/
void ins(TipoRegistro Reg, TipoApontador Ap, short* cresceu, TipoRegistro* RegRetorno, TipoApontador* ApRetorno, Est* est){

    long i = 1;
    long j;
    TipoApontador ApTemp;
    if (Ap == NULL){
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while(i < Ap->n && Reg.key > Ap->r[i-1].key){
        i++;
        incrementaComparacoesC(est);
    }
    
    incrementaComparacoesC(est);
    if (Reg.key == Ap->r[i-1].key){
        printf("Registro ja esta presente\n");
        *cresceu = false;
        return;
    }
    
    if (Reg.key < Ap->r[i-1].key) i--;
    incrementaComparacoesC(est);
    
    ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno, est);
    
    if (!(*cresceu))return;
    if (Ap->n < MM){
        insereNaPagina(Ap, *RegRetorno, *ApRetorno, est);
        *cresceu = false;
        return;
    }

    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if(i < M + 1){
        insereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM], est);
        Ap->n--;
        insereNaPagina(Ap, *RegRetorno, *ApRetorno, est);
    }
    else{
        insereNaPagina(ApTemp, *RegRetorno, *ApRetorno, est);
    }

    for (j = M+2;j <=MM; j++){
        insereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j], est);
    }
    
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

/**
 * Inicializa a inserção de algum item em uma árvore B
*/
void insere(TipoRegistro Reg, TipoApontador *Ap, Est* est){
    short cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    
    ins(Reg, *Ap, &cresceu, &RegRetorno, &ApRetorno, est);

    if (cresceu){
        ApTemp = (TipoPagina*) malloc(sizeof(TipoPagina));
        ApTemp->r[0] = RegRetorno;
        ApTemp->n = 1;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}
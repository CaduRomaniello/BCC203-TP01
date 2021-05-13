#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "BStarTree.h"
#include "estatisticas.h"

typedef struct Page* PagePointer;

// Constructors & Destructors
BStarReg* constructorBStarReg(){
    BStarReg* aux = (BStarReg*)malloc(sizeof(BStarReg));
    if (aux == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }

    aux->key = -1;
    aux->iData = -1;
    strcpy(aux->sData, "");
    return aux;
}
Page* constructorBStarPage(){
    Page* aux = (Page*)malloc(sizeof(Page));
    aux->pointer = -1;
    return aux;
}
void freeBStarReg(BStarReg* reg){
    free(reg);
}
void freeBStarPage(Page* page){
    if (page->pointer == External){
        free(page);
    }
    else{
        for (int i = 0; i < page->UU.U0.nInternal_items; i++){
            freeBStarPage(page->UU.U0.internal_pages[i]);
        }
        free(page);
    }
}

// Set
void setBSKey(BStarReg* reg, int key){
    reg->key = key;
}
void setBSIData(BStarReg* reg, long int iData){
    reg->iData = iData;
}
void setBSSData(BStarReg* reg, char* sData){
    strcpy(reg->sData, sData);
}

// Get
int sizeofBStarReg(){
    return sizeof(BStarReg);
}
int sizeofBSTree(){
    return sizeof(Page);
}
int getBSKey(BStarReg* reg){
    return reg->key;
}
long int getBSIData(BStarReg* reg){
    return reg->iData;
}
char* getBSSData(BStarReg* reg){
    return reg->sData;
}

// Funcoes
/**
 * Equivalente a função ins da árvore B, porém verificando os casos de o nó ser externo ou interno
*/
void insBSTree(BStarReg reg, PagePointer bsTree, short* cresceu, int* regRetorno, PagePointer* returnPointer, Est* est){
    
    long i = 1;
    long j;
    PagePointer pageTemp;

    if (bsTree->pointer == Internal){
        
        while(i < bsTree->UU.U0.nInternal_items && reg.key > bsTree->UU.U0.internal_registries[i-1]){
            i++;
            incrementaComparacoesC(est);
        }
        
        incrementaComparacoesC(est);
        if (reg.key < bsTree->UU.U0.internal_registries[i-1]) i--;
        
        insBSTree(reg, bsTree->UU.U0.internal_pages[i], cresceu, regRetorno, returnPointer, est);
        
        if (!(*cresceu)) return;
        if (bsTree->UU.U0.nInternal_items < MM){
            // insere pagina externa
            internalPageInsert(bsTree, *regRetorno, *returnPointer, est);
            *cresceu = false;
            return;
        }

        pageTemp = (PagePointer)malloc(sizeof(Page));
        pageTemp->pointer = Internal;
        pageTemp->UU.U0.nInternal_items = 0;
        pageTemp->UU.U0.internal_pages[0] = NULL;

        if(i < M + 1){
            // insere pagina interna
            internalPageInsert(pageTemp, bsTree->UU.U0.internal_registries[MM-1], bsTree->UU.U0.internal_pages[MM], est);
            bsTree->UU.U0.nInternal_items--;
            // insere pagina interna
            internalPageInsert(bsTree, *regRetorno, *returnPointer, est);
        }
        else{
            // insere pagina interna
            internalPageInsert(pageTemp, *regRetorno, *returnPointer, est);
        }

        for (j = M+2; j <= MM; j++){
            // insere pagina interna
            internalPageInsert(pageTemp, bsTree->UU.U0.internal_registries[j-1], bsTree->UU.U0.internal_pages[j], est);
        }


        bsTree->UU.U0.nInternal_items = M;
        pageTemp->UU.U0.internal_pages[0] = bsTree->UU.U0.internal_pages[M+1];
        *regRetorno = bsTree->UU.U0.internal_registries[M];
        *returnPointer = pageTemp;
    
    }
    else{

        // insere na pagina externa
        while(i < bsTree->UU.U1.nExternal_items && reg.key > getBSKey(&bsTree->UU.U1.external_registries[i-1])) {
            i++;
            incrementaComparacoesC(est);
        }
        
        incrementaComparacoesC(est);
        if (reg.key == getBSKey(&bsTree->UU.U1.external_registries[i-1])){
            printf("Registro ja esta presente\n");
            *cresceu = false;
            return;
        }

        // Adiciona na página pois ainda tem espaço
        if (bsTree->UU.U1.nExternal_items < MM){
            externalPageInsert(bsTree, reg, NULL, est);
            *cresceu = false;
            return;
        }

        // Overflow: Devemos dividir a página
        pageTemp = (PagePointer)malloc(sizeof(Page));
        pageTemp->pointer = External;
        pageTemp->UU.U1.nExternal_items = 0;

        // O local onde devemos inserir o elemento, neste caso na posicao i
        // for menor ue a metade da minha página atual, devemos inserir na 
        // página existente, caso contrário, inserimos na nova página (pageTemp)
        if(i < M + 1){
            // Insere o último elemento da página atual na nova página
            externalPageInsert(pageTemp, bsTree->UU.U1.external_registries[MM-1], NULL, est);
            bsTree->UU.U1.nExternal_items--;
            externalPageInsert(bsTree, reg, NULL, est);
        }
        else{
            // Insere na nova página o RegRetorno e seu filho a direita
            externalPageInsert(pageTemp, reg, NULL, est);
        }

        // Insere o útimo elemento da página velha na página nova 
        for (j = M+1;j <= MM; j++){
            externalPageInsert(pageTemp, bsTree->UU.U1.external_registries[j-1], NULL, est);
        }

        // Atualiza o valor do número de ítens da página original
        bsTree->UU.U1.nExternal_items = M;

        // Define o 'RegRetorno' como o elemento que sobe para o pai 
        *regRetorno = getBSKey(&(pageTemp->UU.U1.external_registries[0]));

        // Define a nova página como a direita do 'RegRetorno'
        *returnPointer = pageTemp;

    }

    // Define cresceu como true para indicar que algo deve ser feito na pag pai
    *cresceu = true;
}

 /**
 * Equivalente a função insere da árvore B, porém verificando os casos de o nó ser externo ou interno
*/   
void insereBSTree(BStarReg reg, PagePointer* bsTree, Est* est){
    short cresceu;
    
    int regRetorno;
    Page *returnPointer, *tempPointer;

    if ((*bsTree)->pointer == -1){
        tempPointer = (Page*)malloc(sizeof(Page));
        tempPointer->pointer = External;
        tempPointer->UU.U1.nExternal_items = 1;
        tempPointer->UU.U1.external_registries[0] = reg;
        *bsTree = tempPointer;
        return;
    }

    insBSTree(reg, *bsTree, &cresceu, &regRetorno, &returnPointer, est);

    if (cresceu){
        // Cria nova página da raiz
        tempPointer = (Page*)malloc(sizeof(Page));

        // Coloca o elemento
        tempPointer->pointer = Internal;
        tempPointer->UU.U0.internal_registries[0] = regRetorno;

        // Atualiza o número de elementos
        tempPointer->UU.U0.nInternal_items = 1;
        
        // Aponta pagina da direita para a direito do 'RegRetorno'
        tempPointer->UU.U0.internal_pages[1] = returnPointer;

        // Aponta pagina da esquerda para a raiz original
        tempPointer->UU.U0.internal_pages[0] = *bsTree;

        // Atualiza o ponteiro da raiz
        *bsTree = tempPointer;

    }

}

/**
 * Equivalente a função insereNaPagina da árvore B, porém para páginas internas da árvore B*
*/
void internalPageInsert(PagePointer page, int regKey, PagePointer rightPage, Est* est){
   
    short positionNotFound;
    int k;
    
    k = page->UU.U0.nInternal_items;
    positionNotFound = (k > 0);
    
    while(positionNotFound){
        incrementaComparacoesC(est);
        if (regKey >= page->UU.U0.internal_registries[k - 1]){
            positionNotFound = false;
            break;
        }

        page->UU.U0.internal_registries[k] = page->UU.U0.internal_registries[k - 1];
        page->UU.U0.internal_pages[k + 1] = page->UU.U0.internal_pages[k];
        k--;
        if(k < 1) positionNotFound = false;
    }
    
    page->UU.U0.internal_registries[k] = regKey;
    page->UU.U0.internal_pages[k + 1] = rightPage;
    page->UU.U0.nInternal_items++;

}

/**
 * Equivalente a função insereNaPagina da árvore B, porém para páginas externas da árvore B*
*/
void externalPageInsert(PagePointer page, BStarReg reg, PagePointer rightPage, Est* est){
    int nItems = page->UU.U1.nExternal_items;

    nItems++;        
    
    // Find position to insert
    int i = 0;
    int j;

    while(i < page->UU.U1.nExternal_items && getBSKey(&reg) > getBSKey(&(page->UU.U1.external_registries[i]))) {
        i++;
        incrementaComparacoesC(est);
    }
    for (j = nItems - 1; j >= 0; j--){
        if (j > i){
            page->UU.U1.external_registries[j] = page->UU.U1.external_registries[j - 1];
        }
        else if (j == i){
            page->UU.U1.external_registries[j] = reg;
        }
        else{
            continue;
        }
    }
    
    page->UU.U1.nExternal_items++;
    
    return ;
    
}

/**
 * Printa uma árvore B*
*/
void printaBSTree(Page* bsTree){

    if (bsTree->pointer == Internal){

        printf("Interna: ");
        for (int i = 0; i < bsTree->UU.U0.nInternal_items; i++){
            printf("%d ", bsTree->UU.U0.internal_registries[i]);
        }
        printf("\n");

        for (int i = 0; i <= bsTree->UU.U0.nInternal_items; i++){
            printaBSTree(bsTree->UU.U0.internal_pages[i]);
        }

    }
    else{

        printf("Externa: ");
        for (int i = 0; i < bsTree->UU.U1.nExternal_items; i++){
            printf("%d ", bsTree->UU.U1.external_registries[i].key);
        }
        printf("\n");

    }

}

/**
 * Pesquisa um item em uma árvore B* externa
*/
void searchBSTree(Page* bsTree, BStarReg* reg, FILE* input, Est* est){

    int i = 1, position;

    if (bsTree->pointer == Internal){

        while(i < bsTree->UU.U0.nInternal_items && reg->key > bsTree->UU.U0.internal_registries[i-1]) {
            i++;
            incrementaComparacoesP(est);
        }

        incrementaComparacoesP(est);
        if (reg->key < bsTree->UU.U0.internal_registries[i-1]) i--;

        position = bsTree->UU.U0.intPointer[i];
        fseek(input, sizeofBSTree() * position, SEEK_SET);
        fread(bsTree, sizeofBSTree(), 1, input);
        
        incrementaFseekP(est);
        incrementaFreadP(est);
        
        if (VERBOSE){
            printf("%d (Interna) ", bsTree->UU.U0.internal_registries[i-1]);
        }

        searchBSTree(bsTree, reg, input, est);

    }
    else{

        for (int i = 0; i < bsTree->UU.U1.nExternal_items; i++){
            incrementaComparacoesP(est);
            if (reg->key == bsTree->UU.U1.external_registries[i].key){
                reg->iData = getBSIData(&(bsTree->UU.U1.external_registries[i]));
                strcpy(reg->sData, getBSSData(&(bsTree->UU.U1.external_registries[i])));
                return;
            } else{
                if (VERBOSE){
                    printf("%d (Externa) ", bsTree->UU.U1.external_registries[i].key);
                }
            }
        }

    }

}

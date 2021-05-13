#ifndef BSTARTREE_H
#define BSTARTREE_H
#include <stdbool.h>
#include "estatisticas.h"

#define M 2
#define MM 2*M

typedef enum{External, Internal} PageType;
typedef struct Page* PagePointer;
typedef struct Page Page;
typedef struct BStarReg BStarReg;

typedef struct BStarReg{
    
    int key;
    long int iData;
    char sData[500];

} BStarReg;

typedef struct Page{

    PageType pointer;

    union {
        struct {
            int nInternal_items;
            int internal_registries[MM];
            PagePointer internal_pages[MM + 1];
            
            int intPointer[MM + 1];
        } U0;
        struct {
            int nExternal_items;
            BStarReg external_registries[MM];
        } U1;
    } UU;

    int position;

} Page;

// Constructors
BStarReg* constructorBStarReg();
Page* constructorBStarPage();
void freeBStarReg(BStarReg* reg);
void freeBStarPage(Page* page);

// Set
void setBSKey(BStarReg* reg, int key);
void setBSIData(BStarReg* reg, long int iData);
void setBSSData(BStarReg* reg, char* sData);

// Get
int sizeofBStarReg();
int sizeofBSTree();
int getBSKey(BStarReg* regs);
long int getBSIData(BStarReg* regs);
char* getBSSData(BStarReg* regs);

// Funcoes
void insereBSTree(BStarReg reg, PagePointer* bsTree, Est* est);
void internalPageInsert(PagePointer page, int regKey, PagePointer rightPage, Est* est);
void externalPageInsert(PagePointer page, BStarReg reg, PagePointer rightPage, Est* est);
void insBSTree(BStarReg reg, PagePointer bsTree, short* cresceu, int* regRetorno, PagePointer* returnPointer, Est* est);

// Debug
void printaBSTree(Page* bsTree);

// Search
void searchBSTree(Page* bsTree, BStarReg* reg, FILE* input, Est* est);

#endif
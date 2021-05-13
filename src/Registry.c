#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Registry.h"

int PAGE_BLOCK = 50;

// Construtores
Regs* constructorRegs(){
    Regs* reg = (Regs*) malloc(sizeof(Regs));
    if (reg == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }

    reg->key = -1;
    reg->iData = -1;
    strcpy(reg->sData, "");

    return reg;
}

void freeReg(Regs* reg){
    free(reg);
}

// Gets
int sizeofReg(){
    return sizeof(struct registry);
}

int getIndividualKey(Regs* regs){
    return regs->key;
}

long int getIndividualIData(Regs* regs){
    return regs->iData;
}

char* getIndividualSData(Regs* regs){
    return regs->sData;
}

int getKey(Regs* regs, int position){
    return regs[position].key;
}

long int getIData(Regs* regs, int position){
    return regs[position].iData;
}

char* getSData(Regs* regs, int position){
    return regs[position].sData;
}

//Sets
void setKey(Regs* reg, int key){
    reg->key = key;
}

void setIData(Regs* reg, long int iData){
    reg->iData = iData;
}

void setSData(Regs* reg, char* sData){
    strcpy(reg->sData, sData);
}
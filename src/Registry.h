#ifndef REGISTRY_H
#define REGISTRY_H

typedef struct registry {
    int key;
    long int iData;
    char sData[500];
}Regs;
int PAGE_BLOCK;

Regs* constructorRegs();
void freeReg(Regs* reg);

int sizeofReg();
int getIndividualKey(Regs* regs);
long int getIndividualIData(Regs* regs);
char* getIndividualSData(Regs* regs);
int getKey(Regs* regs, int position);
long int getIData(Regs* regs, int position);
char* getSData(Regs* regs, int position);

void setKey(Regs* reg, int key);
void setIData(Regs* reg, long int iData);
void setSData(Regs* reg, char* sData);

#endif
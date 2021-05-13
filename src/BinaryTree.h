#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <stdbool.h>
#include "Registry.h"
#include "estatisticas.h"

typedef struct binTree BinTree;

void writeBinTree(FILE* input, BinTree* bin, Est* est);
void readBinTree(FILE* input, BinTree* bin, Est* est, int filter);

int sizeofBinTree();
BinTree* constructorBinTree();
void freeBinTree(BinTree* bin);

Regs* getRegistry(BinTree* node);
int getPDir(BinTree* node);
int getPEsq(BinTree* node);
int getPosition(BinTree* node);

void setReg(BinTree* node, Regs* reg);
void setPDir(BinTree* node, int p);
void setPEsq(BinTree* node, int p);
void setPosition(BinTree* node, int position);


void searchBinTree(BinTree* pagePointer, Regs* registry, int key, FILE* tree, Est* est);

int FBBinary (BinTree* node, FILE* input, Est* est);
int heightBinaryTree(BinTree* node, FILE* input, Est* est);
void RSEBinary(BinTree* node, FILE* input, Est* est);
void RSDBinary (BinTree* node, FILE* input, Est* est);
int leftBalance(BinTree* node, FILE* input, Est* est); 
int rightBalance(BinTree* node, FILE* input, Est* est);
int balanceBinaryTree(BinTree* node, FILE* input, Est* est);

int insertBinaryTree(FILE* input, BinTree* node, BinTree* item, int root, int* count, Est* est);

#endif
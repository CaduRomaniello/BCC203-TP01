#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "BinaryTree.h"
#include "estatisticas.h"

typedef struct binTree{
    
    Regs* reg;
    int pDir, pEsq;
    int position;

}BinTree;

/**
 * Escreve um nó da árvore binária em um arquivo
*/
void writeBinTree(FILE* input, BinTree* bin, Est* est){

    int pEsq = getPEsq(bin);
    int pDir = getPDir(bin);
    int pos = getPosition(bin);
    
    fwrite(getRegistry(bin), sizeofReg(), 1, input);
    fwrite(&pEsq, sizeof(int), 1, input);
    fwrite(&pDir, sizeof(int), 1, input);
    fwrite(&pos, sizeof(int), 1, input);

    incrementaFwriteC(est);
    incrementaFwriteC(est);
    incrementaFwriteC(est);
    incrementaFwriteC(est);

}

/**
 * Lê um nó da árvore binária de um arquivo
*/
void readBinTree(FILE* input, BinTree* bin, Est* est, int filter){

    Regs* reg = constructorRegs();
    int pEsq;
    int pDir;
    int pos;

    fread(reg, sizeofReg(), 1, input);
    fread(&pEsq, sizeof(int), 1, input);
    fread(&pDir, sizeof(int), 1, input);
    fread(&pos, sizeof(int), 1, input);
    
    setReg(bin, reg);
    setPEsq(bin, pEsq);
    setPDir(bin, pDir);
    setPosition(bin, pos);
    
    if (filter == 1){
        incrementaFreadC(est);
        incrementaFreadC(est);
        incrementaFreadC(est);
        incrementaFreadC(est);
    } else {
        incrementaFreadP(est);
        incrementaFreadP(est);
        incrementaFreadP(est);
        incrementaFreadP(est);
    }

}

int sizeofBinTree(){
    return sizeofReg() + (3 * sizeof(int));
}

BinTree* constructorBinTree(){
    BinTree* aux = (BinTree*) malloc(sizeof(BinTree));
    aux->reg = constructorRegs();
    return aux;
}

void freeBinTree(BinTree* bin){
    freeReg(bin->reg);
    free(bin);
}

Regs* getRegistry(BinTree* node){
    return node->reg;
}

int getPDir(BinTree* node){
    return node->pDir;
}

int getPEsq(BinTree* node){
    return node->pEsq;
}

int getPosition(BinTree* node){
    return node->position;
}

void setReg(BinTree* node, Regs* reg){
    node->reg = reg;
}

void setPDir(BinTree* node, int p){
    node->pDir = p;
}

void setPEsq(BinTree* node, int p){
    node->pEsq = p;
}

void setPosition(BinTree* node, int position){
    node->position = position;
}

/**
 * Faz a pesquisa de um item em uma árvore binária externa
*/
void searchBinTree(BinTree* node, Regs* registry, int key, FILE* tree, Est* est){

    
    // Check if node is leaf
    if (getPEsq(node) == -1 && getPDir(node) == -1 && getIndividualKey(getRegistry(node)) != key){
        incrementaComparacoesP(est);

        if (VERBOSE){
            printf("%d ", getIndividualKey(getRegistry(node)));
        }

        return;
    } 

    if(getIndividualKey(getRegistry(node)) == key) {
        incrementaComparacoesP(est);
        setKey(registry, getIndividualKey(getRegistry(node)));
        setIData(registry, getIndividualIData(getRegistry(node)));
        setSData(registry, getIndividualSData(getRegistry(node)));
        
        return;
    } else {
        if (VERBOSE){
            printf("%d ", getIndividualKey(getRegistry(node)));
        }
    }

    if (key < getIndividualKey(getRegistry(node))){
        incrementaComparacoesP(est);
        
        // Set pointer to the next node position
        fseek(tree, (getPEsq(node) * sizeofBinTree()) + sizeof(int), SEEK_SET);
        readBinTree(tree, node, est, 1);
        incrementaFseekP(est);

        // Search on next node
        searchBinTree(node, registry, key, tree, est);

    } else {
       
        // Set pointer to the next node position
        fseek(tree, (getPDir(node) * sizeofBinTree()) + sizeof(int), SEEK_SET);
        readBinTree(tree, node, est, 1);
        incrementaFseekP(est);

        // Search on next node
        searchBinTree(node, registry, key, tree, est);

    }

    return;

}

int FBBinary (BinTree* node, FILE* input, Est* est) {

    if (getPosition(node) == -1){
        return 0;
    }

    int pDir = getPDir(node);
    int pEsq = getPEsq(node);
    
    BinTree* rightSon = constructorBinTree();
    BinTree* leftSon  = constructorBinTree();

    if (pEsq == -1){
        setPosition(leftSon, -1);
    }
    else{
        fseek(input, sizeof(int) + (pEsq * sizeofBinTree()), SEEK_SET);
        readBinTree(input, leftSon, est, 1);

        incrementaFseekC(est);
    }

    if (pDir == -1){
        setPosition(rightSon, -1);
    }
    else{
        fseek(input, sizeof(int) + (pDir * sizeofBinTree()), SEEK_SET);
        readBinTree(input, rightSon, est, 1);

        incrementaFseekC(est);
    }

    int diff = heightBinaryTree(leftSon, input, est) - heightBinaryTree(rightSon, input, est);
    freeBinTree(rightSon);
    freeBinTree(leftSon);

    return diff;

}

int heightBinaryTree(BinTree* node, FILE* input, Est* est) {
    
    int left, right;
    
    if (getPosition(node) == -1){
        return 0;
    }

    int pDir = getPDir(node);
    int pEsq = getPEsq(node);
    
    BinTree* leftChild = constructorBinTree();
    BinTree* rightChild  = constructorBinTree();

    if (pEsq == -1){
        setPosition(leftChild, -1);
    }
    else{
        fseek(input, sizeof(int) + (pEsq * sizeofBinTree()), SEEK_SET);
        readBinTree(input, leftChild, est, 1);
        
        incrementaFseekC(est);
    }

    if (pDir == -1){
        setPosition(rightChild, -1);
    }
    else{
        fseek(input, sizeof(int) + (pDir * sizeofBinTree()), SEEK_SET);
        readBinTree(input, rightChild, est, 1);

        incrementaFseekC(est);
    }

    left = heightBinaryTree(leftChild, input, est);
    right = heightBinaryTree(rightChild, input, est);

    freeBinTree(rightChild);
    freeBinTree(leftChild);

    if (left > right){
        return left + 1;
    } else{
        return right + 1;
    }

}

void RSEBinary(BinTree* node, FILE* input, Est* est) {

    BinTree* aux = constructorBinTree();
    
    fseek(input, sizeof(int) + (getPDir(node) * sizeofBinTree()), SEEK_SET);
    readBinTree(input, aux, est, 1);
    incrementaFseekC(est);
    
    int posNode = getPosition(node);
    int posSon = getPosition(aux);
    
    setPDir(node, getPEsq(aux));
    setPEsq(aux, getPosition(aux));

    setPosition(node, posSon);
    setPosition(aux, posNode);
    
    fseek(input, sizeof(int) + (posNode * sizeofBinTree()), SEEK_SET);
    incrementaFseekC(est);

    writeBinTree(input, aux, est);

    fseek(input, sizeof(int) + (posSon * sizeofBinTree()), SEEK_SET);
    incrementaFseekC(est);
    
    writeBinTree(input, node, est);

    freeBinTree(aux);

}

void RSDBinary (BinTree* node, FILE* input, Est* est) {
    
    BinTree* aux = constructorBinTree();
    

    fseek(input, sizeof(int) + (getPEsq(node) * sizeofBinTree()), SEEK_SET);
    readBinTree(input, aux, est, 1);
    incrementaFseekC(est);
    
    int posNode = getPosition(node);
    int posSon = getPosition(aux);
    
    setPEsq(node, getPDir(aux));
    setPDir(aux, getPosition(aux));

    setPosition(node, posSon);
    setPosition(aux, posNode);
    
    fseek(input, sizeof(int) + (posNode * sizeofBinTree()), SEEK_SET);
    incrementaFseekC(est);

    writeBinTree(input, aux, est);

    fseek(input, sizeof(int) + (posSon * sizeofBinTree()), SEEK_SET);
    incrementaFseekC(est);
    
    writeBinTree(input, node, est);

    freeBinTree(aux);
    
}

int leftBalance(BinTree* node, FILE* input, Est* est) {

    BinTree* leftSon = constructorBinTree();

    if (getPEsq(node) == -1){
        setPosition(leftSon, -1);
    }
    else{
        fseek(input, sizeof(int) + (getPEsq(node) * sizeofBinTree()), SEEK_SET);
        readBinTree(input, leftSon, est, 1);

        incrementaFseekC(est);
    }

    int fbe =  FBBinary (leftSon, input, est);
    if ( fbe >  0 ){
        RSDBinary(node, input, est);
        freeBinTree(leftSon);
        return 1;
    } else if (fbe <  0 ) { /* Rotação Dupla Direita */
        RSEBinary(leftSon, input, est);
        RSDBinary(node, input, est);
        freeBinTree(leftSon);
        return 1;
    }
    
    return 0;
}

int rightBalance(BinTree* node, FILE* input, Est* est) {

    BinTree* rightSon = constructorBinTree();

    if (getPDir(node) == -1){
        setPosition(rightSon, -1);
    }
    else{
        fseek(input, sizeof(int) + (getPDir(node) * sizeofBinTree()), SEEK_SET);
        readBinTree(input, rightSon, est, 1);
        
        incrementaFseekC(est);
    }

    int fbd = FBBinary(rightSon, input, est);
    if (fbd < 0) {
        RSEBinary (node, input, est);
        freeBinTree(rightSon);
        return 1;
    } else if (fbd > 0 ) { /* Rotação Dupla Esquerda*/
        RSDBinary(rightSon, input, est);
        RSEBinary(node, input, est);
        freeBinTree(rightSon);
        return 1;
    }
    return 0;
}

int balanceBinaryTree(BinTree* node, FILE* input, Est* est){

    int fb = FBBinary(node, input, est);

    if (fb >  1){
        return leftBalance(node, input, est);
    }
    else if(fb < -1){
        return rightBalance(node, input, est);
    }
    else 
        return 0;

}

/**
 * Insere um item em uma árvore binária externa
*/
int insertBinaryTree(FILE* input, BinTree* node, BinTree* item, int root, int* count, Est* est){

    // Criando uma cópia do nó passado por parâmetro
    BinTree* copy = constructorBinTree();
    setKey(getRegistry(copy), getIndividualKey(getRegistry(node)));
    setIData(getRegistry(copy), getIndividualIData(getRegistry(node)));
    setSData(getRegistry(copy), getIndividualSData(getRegistry(node)));
    setPEsq(copy, getPEsq(node));
    setPDir(copy, getPDir(node));
    setPosition(copy, getPosition(node));

    // Caso tenha chegado em um nó folha, verifica as condições, caso contrário verifica em qual nó a pesquisa deve continuar
    if (getPosition(node) == -1){
        // Se não existir raiz, é criado uma, caso contrário retorna
        if (root == -1){
            rewind(input);
            incrementaFseekC(est);

            int p = getPosition(item);
            fflush(input);
            fwrite(&p, sizeof(int), 1, input);
            fseek(input, 0, SEEK_END);

            incrementaFwriteC(est);
            incrementaFseekC(est);
        }
        freeBinTree(copy);
        return 1;
    }
    //Pesquisa no nó da esquerda
    else if (getIndividualKey(getRegistry(node)) > getIndividualKey(getRegistry(item))){
        incrementaComparacoesC(est);

        if (getPEsq(node) == -1){ // Se o nó não tiver filho á esquerda, insere o item à esquerda do nó atual e atualiza o arquivo
            setPEsq(node, getPosition(item));
            fseek(input, sizeof(int) + (getPosition(node) * sizeofBinTree()), SEEK_SET);
            incrementaFseekC(est);

            fflush(input);
            writeBinTree(input, node, est);
            setPosition(node, -1);

            fseek(input, 0, SEEK_END);
            incrementaFseekC(est);
        }
        else{ // Caso contrário lê o próximo nó
            fseek(input, sizeof(int) + (getPEsq(node) * sizeofBinTree()), SEEK_SET);
            readBinTree(input, node, est, 1);
            fseek(input, 0, SEEK_END);
            
            incrementaFseekC(est);
            incrementaFseekC(est);
        }

        if (insertBinaryTree(input, node, item, root, count, est)){ // Se a inserção ocorreu com sucesso, a árvore será balanceada

            setKey(getRegistry(node), getIndividualKey(getRegistry(copy)));
            setIData(getRegistry(node), getIndividualIData(getRegistry(copy)));
            setSData(getRegistry(node), getIndividualSData(getRegistry(copy)));
            setPDir(node, getPDir(copy));
            setPEsq(node, getPEsq(copy));
            setPosition(node, getPosition(copy));
            freeBinTree(copy);

            if (balanceBinaryTree(node, input, est)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    //Pesquisa no nó da direita
    else if (getIndividualKey(getRegistry(node)) < getIndividualKey(getRegistry(item))){
        incrementaComparacoesC(est);

        if (getPDir(node) == -1){ // Se o nó não tiver filho á direita, insere o item à direita do nó atual e atualiza o arquivo
            setPDir(node, getPosition(item));
            fseek(input, sizeof(int) + (getPosition(node) * sizeofBinTree()), SEEK_SET);
            incrementaFseekC(est);

            fflush(input);
            writeBinTree(input, node, est);
            setPosition(node, -1);
            
            fseek(input, 0, SEEK_END);
            incrementaFseekC(est);
        }
        else{ // Caso contrário lê o próximo nó
            fseek(input, sizeof(int) + (getPDir(node) * sizeofBinTree()), SEEK_SET);
            readBinTree(input, node, est, 1);
            fseek(input, 0, SEEK_END);
            
            incrementaFseekC(est);
            incrementaFseekC(est);
        }

        if (insertBinaryTree(input, node, item, root, count, est)){ // Se a inserção ocorreu com sucesso, a árvore será balanceada

            setKey(getRegistry(node), getIndividualKey(getRegistry(copy)));
            setIData(getRegistry(node), getIndividualIData(getRegistry(copy)));
            setSData(getRegistry(node), getIndividualSData(getRegistry(copy)));
            setPEsq(node, getPEsq(copy));
            setPDir(node, getPDir(copy));
            setPosition(node, getPosition(copy));
            freeBinTree(copy);
            
            if (balanceBinaryTree(node, input, est)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else{
        freeBinTree(copy);
        return 0;
    }

    return 0;

}
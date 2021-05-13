#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "construirArquivo.h"
#include "BinaryTree.h"
#include "BinTree.h"
#include "BTree.h"
#include "BStarTree.h"
#include "Registry.h"
#include "estatisticas.h"
#include "Sort.h"

#define sizeOfString 5
/**
 * Cria uma string aleatória de tamanho sizeOfString
*/
void criaString(char* word){

    int size = sizeOfString;

    for (int i = 0; i < size; i++){
        char aux = ((rand() % 25) + 65);
        word[i] = aux;
    }
    word[sizeOfString] = '\0';

}

/**
 * Método utilizado para a geração de chaves aleatórias no caso de ordenação 3
*/
int verificaUsoChave(int* vet, int qntd, int chave){
    for (int i = 0; i < qntd; i++){
        if (vet[i] == chave){
            return 1;
        }
    }

    return 0;
}
/**
 * Corrige os ponteiros de arquivo da árvore binária
*/
void corrigePonteirosArvoreBinaria(TNo* arvore, int* count){

    if (arvore == NULL){
        return;
    }
    else{
        arvore->posicao = *count;

        if (arvore->pEsq != NULL){
            arvore->iEsq = ++(*count);
            corrigePonteirosArvoreBinaria(arvore->pEsq, count);
        }
        else{
            arvore->iEsq = -1;
        }
        if (arvore->pDir != NULL){
            arvore->iDir = ++(*count);
            corrigePonteirosArvoreBinaria(arvore->pDir, count);
        }
        else{
            arvore->iDir = -1;
        }
    }
}

/**
 * Escreve uma árvore binária em um arquivo
*/
void escreveArvoreBinaria(TNo* arvore, FILE* input, Est* est){

    if (arvore != NULL){
        fwrite(arvore, sizeof(TNo), 1, input);
        incrementaFwriteC(est);

        escreveArvoreBinaria(arvore->pEsq, input, est);
        escreveArvoreBinaria(arvore->pDir, input, est);
    }

}

/**
 * Corrige os ponteiros de arquivo de uma árvore B
*/
void corrigePonteiros(TipoPagina* bTree, int* count){

    if (bTree->p[0] == NULL){
        bTree->position = *count;
        for (int i = 0; i <= bTree->n; i++){
            bTree->intPointer[i] = -1;
        }
    }
    else{
        bTree->position = *count;
        for (int i = 0; i <= bTree->n; i++){
            bTree->intPointer[i] = ++(*count);
            corrigePonteiros(bTree->p[i], count);
        }
    }

}

/**
 * Escreve uma árvore B interna em um arquivo
*/
void escreveBTree(TipoPagina* bTree, FILE* input, Est* est){

    if (bTree->p[0] == NULL){
        fwrite(bTree, sizeofBTree(), 1, input);
        incrementaFwriteC(est);
    }
    else{
        fwrite(bTree, sizeofBTree(), 1, input);
        incrementaFwriteC(est);

        for (int i = 0; i <= bTree->n; i++){
            escreveBTree(bTree->p[i], input, est);
        }
    }

}

/**
 * Corrige os ponteiros de arquivo de uma árvore B*
*/
void corrigePonteirosBSTree(Page* bsTree, int* count){

    if (bsTree->pointer == Internal){
        bsTree->position = *count;
        for (int i = 0; i <= bsTree->UU.U0.nInternal_items; i++){
            bsTree->UU.U0.intPointer[i] = ++(*count);
            corrigePonteirosBSTree(bsTree->UU.U0.internal_pages[i], count);
        }
    }
    else{
        bsTree->position = *count;
    }

}

/**
 * Escreve uma árvore B* em uma rquivo
*/
void escreveBStarTree(Page* bsTree, FILE* input, Est* est){

    if (bsTree->pointer == External){
        fwrite(bsTree, sizeofBSTree(), 1, input);
        incrementaFwriteC(est);
    }
    else{
        fwrite(bsTree, sizeofBSTree(), 1, input);
        incrementaFwriteC(est);

        for (int i = 0; i <= bsTree->UU.U0.nInternal_items; i++){
            escreveBStarTree(bsTree->UU.U0.internal_pages[i], input, est);
        }
    }

}

/**
 * Cria o arquivo binário de Acesso Sequncial Indexado
*/
void criarArquivoSequencial(char* arq, int qntd, int ordenacao, Est* est){
    
    FILE* input = fopen(arq, "w+b");
    Regs *reg = constructorRegs(), *regAux = constructorRegs();

    if (ordenacao == 1){

        Regs* vetReg = malloc(qntd * sizeofReg());

        for (int i = 1; i <= qntd; i++){

            setKey(&(vetReg[i - 1]), i);
            setIData(&(vetReg[i - 1]), (rand()%qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setSData(&(vetReg[i - 1]), word);

        }
        
        fwrite(vetReg, sizeofReg(), qntd, input);
        incrementaFwriteC(est);

        free(vetReg);

    }
    else if (ordenacao == 2){

        Regs* vetReg = malloc(qntd * sizeofReg());

        int pos = 0;
        for (int i = qntd; i > 0; i--){

            setKey(&(vetReg[pos]), i);
            setIData(&(vetReg[pos]), (rand()%qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setSData(&(vetReg[pos]), word);
            pos++;

        }

        quick_sort(vetReg, qntd, est);
        
        fwrite(vetReg, sizeofReg(), qntd, input);
        incrementaFwriteC(est);

        free(vetReg);

    }
    else{

        char arqTxt[10];
        sprintf(arqTxt, "%d", qntd);
        char dir[50] = "../input/";
        strcat(dir, arqTxt);
        strcat(dir, ".txt");
        FILE* arqReg = fopen(dir, "r");

        int chaveReg;
        char enter;
        Regs* vetReg = malloc(qntd * sizeofReg());

        for (int i = 0; i < qntd; i++){

            fscanf(arqReg, "%d %[\n]", &chaveReg, &enter);

            setKey(&(vetReg[i]), chaveReg);
            setIData(&(vetReg[i]), (rand()%qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setSData(&(vetReg[i]), word);

            incrementaFreadC(est);

        }

        fclose(arqReg);

        quick_sort(vetReg, qntd, est);
        
        fwrite(vetReg, sizeofReg(), qntd, input);
        incrementaFwriteC(est);
        free(vetReg);

    }
    

    fclose(input);
    free(reg);
    free(regAux);
}

/**
 * Cria o arquivo binário de Árvore Binária
*/
void criarArqBinTree(char* arq, int qntd, int ordenacao, Est* est){

    TNo* bin;
    bin = NULL;
    FILE* input = fopen(arq, "wb+");
    int count = 0;
    
    if (ordenacao == 1){

        for (int i = 1; i <= qntd; i++){

            TItem* item = criaTItem();
            setBinKeyItem(item, i);
            setBinIDataItem(item, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBinSDataItem(item, word);

            Insere(&bin, item, est);
            liberaTItem(item);

        }

        corrigePonteirosArvoreBinaria(bin, &count);
        escreveArvoreBinaria(bin, input, est);

    }
    else if (ordenacao == 2){
        
        for (int i = qntd; i > 0; i--){
            TItem* item = criaTItem();
            setBinKeyItem(item, i);
            setBinIDataItem(item, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBinSDataItem(item, word);

            Insere(&bin, item, est);
            liberaTItem(item);

        }

        corrigePonteirosArvoreBinaria(bin, &count);
        escreveArvoreBinaria(bin, input, est);

    }
    else{

        char arqTxt[10];
        sprintf(arqTxt, "%d", qntd);
        char dir[50] = "../input/";
        strcat(dir, arqTxt);
        strcat(dir, ".txt");
        FILE* arqReg = fopen(dir, "r");

        int chaveReg;
        char enter;

        for (int i = 0; i < qntd; i++){

            fscanf(arqReg, "%d %[\n]", &chaveReg, &enter);
            incrementaFreadC(est);

            TItem* item = criaTItem();
            setBinKeyItem(item, chaveReg);
            setBinIDataItem(item, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBinSDataItem(item, word);

            Insere(&bin, item, est);
            liberaTItem(item);
        }

        corrigePonteirosArvoreBinaria(bin, &count);
        escreveArvoreBinaria(bin, input, est);

    }


    liberaTNo(bin);
    fclose(input);
}

/**
 * Cria o arquivo binário de Árvore B
*/
void criarArqBTree(char* arq, int qntd, int ordenacao, int key, Est* est){

    int count = 0;

    TipoPagina* bTree;
    bTree = NULL;
    FILE* input = fopen(arq, "wb+");

    if (ordenacao == 1){
        for (int i = 1; i <= qntd; i++){
            TipoRegistro* reg = constructorTipoRegistro();
            setChave(reg, i);
            setDadoInteiro(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setDadoString(reg, word);

            insere(*reg, &bTree, est);

            freeTipoRegistro(reg);
        }
    }
    else if (ordenacao == 2){

        for (int i = qntd; i > 0; i--){
            TipoRegistro* reg = constructorTipoRegistro();
            setChave(reg, i);
            setDadoInteiro(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setDadoString(reg, word);

            insere(*reg, &bTree, est);

            freeTipoRegistro(reg);
        }

    }
    else{

        char arqTxt[10];
        sprintf(arqTxt, "%d", qntd);
        char dir[50] = "../input/";
        strcat(dir, arqTxt);
        strcat(dir, ".txt");
        FILE* arqReg = fopen(dir, "r");

        int chaveReg;
        char enter;

        for (int i = 0; i < qntd; i++){

            fscanf(arqReg, "%d %[\n]", &chaveReg, &enter);
            incrementaFreadC(est);


            TipoRegistro* reg = constructorTipoRegistro();
            setChave(reg, chaveReg);
            setDadoInteiro(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setDadoString(reg, word);

            insere(*reg, &bTree, est);

            freeTipoRegistro(reg);

        }

        fclose(arqReg);

    }

    corrigePonteiros(bTree, &count);
    escreveBTree(bTree, input, est);

    liberaPagina(bTree);
    fclose(input);

}

/**
 * Cria o arquivo binário de Árvore B*
*/
void criarArqBStarTree(char* arq, int qntd, int ordenacao, int key, Est* est){

    int count = 0;

    Page* bsTree = constructorBStarPage();
    FILE* input = fopen(arq, "wb+");

    if (ordenacao == 1){
        for (int i = 1; i <= qntd; i++){
            BStarReg* reg = constructorBStarReg();
            setBSKey(reg, i);
            setBSIData(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBSSData(reg, word);

            insereBSTree(*reg, &bsTree, est);

            freeBStarReg(reg);
        }
    }
    else if (ordenacao == 2){

        for (int i = qntd; i > 0; i--){
            BStarReg* reg = constructorBStarReg();
            setBSKey(reg, i);
            setBSIData(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBSSData(reg, word);

            insereBSTree(*reg, &bsTree, est);

            freeBStarReg(reg);
        }

    }
    else{

        char arqTxt[10];
        sprintf(arqTxt, "%d", qntd);
        char dir[50] = "../input/";
        strcat(dir, arqTxt);
        strcat(dir, ".txt");
        FILE* arqReg = fopen(dir, "r");

        int chaveReg;
        char enter;

        for (int i = 0; i < qntd; i++){

            fscanf(arqReg, "%d %[\n]", &chaveReg, &enter);
            incrementaFreadC(est);

            BStarReg* reg = constructorBStarReg();
            setBSKey(reg, chaveReg);
            setBSIData(reg, (rand() %qntd + 1));
            char word[sizeOfString + 1];
            criaString(word);
            setBSSData(reg, word);

            insereBSTree(*reg, &bsTree, est);

            freeBStarReg(reg);

        }

        fclose(arqReg);

    }

    corrigePonteirosBSTree(bsTree, &count);
    escreveBStarTree(bsTree, input, est);

    freeBStarPage(bsTree);
    fclose(input);

}









/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//                     Código mencionado no arquivo README.md                      //
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Codigo para criacao de arvore binaria externa
// void criarArqBinTree(char* arq, int qntd, int ordenacao, Est* est){

//     int count = 0;
//     char dir[100] = "../";
//     strcat(dir, arq);

//     BinTree* bin = constructorBinTree();
//     FILE* input = fopen(arq, "wb+");
//     int x = -1;
    
//     fwrite(&x, sizeof(int), 1, input);
//     incrementaFwriteC(est);

//     if (ordenacao == 1){

//         for (int i = 1; i <= qntd; i++){

//             setKey(getRegistry(bin), i);
//             setIData(getRegistry(bin), (rand() %qntd + 1));
//             char word[sizeOfString + 1];
//             criaString(word);
//             setSData(getRegistry(bin), word);

//             setPEsq(bin, -1);
//             setPDir(bin, -1);
//             setPosition(bin, i - 1);

//             writeBinTree(input, bin, est);

//             int root;
//             rewind(input);
//             fread(&root, sizeof(int), 1, input);

//             incrementaFseekC(est);
//             incrementaFreadC(est);

//             BinTree* aux = constructorBinTree();
//             if (root == -1){
//                 setPosition(aux, -1);
//             }
//             else{
//                 fseek(input, sizeof(int) + (root * sizeofBinTree()), SEEK_SET);
//                 incrementaFseekC(est);

//                 readBinTree(input, aux, est, 1);
//             }


//             // Insert item
//             insertBinaryTree(input, aux, bin, root, &count, est);

//             fseek(input, 0, SEEK_END);
//             incrementaFseekC(est);

//             freeBinTree(aux);

//         }
//     }
//     else if(ordenacao == 2){

//         int countPos = 0;
//         for (int i = qntd; i > 0; i--){

//             setKey(getRegistry(bin), i);
//             setIData(getRegistry(bin), (rand() %qntd + 1));
//             char word[sizeOfString + 1];
//             criaString(word);
//             setSData(getRegistry(bin), word);

//             setPEsq(bin, -1);
//             setPDir(bin, -1);
//             setPosition(bin, countPos);
//             countPos++;

//             writeBinTree(input, bin, est);


//             int root;
//             rewind(input);
//             fread(&root, sizeof(int), 1, input);

//             incrementaFseekC(est);
//             incrementaFreadC(est);

//             BinTree* aux = constructorBinTree();
//             if (root == -1){
//                 setPosition(aux, -1);
//             }
//             else{
//                 fseek(input, sizeof(int) + (root * sizeofBinTree()), SEEK_SET);
//                 incrementaFseekC(est);

//                 readBinTree(input, aux, est, 1);
//             }


//             // Insert item
//             insertBinaryTree(input, aux, bin, root, &count, est);

//             fseek(input, 0, SEEK_END);
//             incrementaFseekC(est);

//             freeBinTree(aux);

//         }

//     }
//     else{

//         char arqTxt[10];
//         sprintf(arqTxt, "%d", qntd);
//         char dir[50] = "../input/";
//         strcat(dir, arqTxt);
//         strcat(dir, ".txt");
//         FILE* arqReg = fopen(dir, "r");

//         int countPos = 0;
//         int chaveReg;
//         char enter;

//         for (int i = 0; i < qntd; i++){

//             printf("COUNT: %d\n", i);
//             fscanf(arqReg, "%d %[\n]", &chaveReg, &enter);
            
//             setKey(getRegistry(bin), chaveReg);
//             setIData(getRegistry(bin), (rand() %qntd + 1));
//             char word[sizeOfString + 1];
//             criaString(word);
//             setSData(getRegistry(bin), word);

//             setPEsq(bin, -1);
//             setPDir(bin, -1);
//             setPosition(bin, countPos);
//             countPos++;

//             writeBinTree(input, bin, est);


//             int root;
//             rewind(input);
//             fread(&root, sizeof(int), 1, input);

//             incrementaFseekC(est);
//             incrementaFreadC(est);

//             BinTree* aux = constructorBinTree();
//             if (root == -1){
//                 setPosition(aux, -1);
//             }
//             else{
//                 fseek(input, sizeof(int) + (root * sizeofBinTree()), SEEK_SET);
//                 incrementaFseekC(est);

//                 readBinTree(input, aux, est, 1);
//             }


//             // Insert Item
//             insertBinaryTree(input, aux, bin, root, &count, est);

//             fseek(input, 0, SEEK_END);
//             incrementaFseekC(est);

//             freeBinTree(aux);

//         }

//     }

//     freeBinTree(bin);
//     fclose(input);
// }
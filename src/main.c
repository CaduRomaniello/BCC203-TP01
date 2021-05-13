// ./pesquisa arvoreB 10000 1 10 p

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "Sequential.h"
#include "BinaryTree.h"
#include "BTree.h"
#include "BStarTree.h"
#include "Registry.h"
#include "construirArquivo.h"
#include "estatisticas.h"
#include "Sort.h"

void help();
void printaArquivoArvoreBinaria(char* string, int qntd, Est* est);
void printaArquivoASI(char* string);
bool VERBOSE = false;
int TOTAL_LINES = 0;

/**
 * Trabalho de Estrutura de dados II - UFOP - 2021
 * 
 * Professor:
 *      - Guilherme Tavares de Assis
 *
 * Alunos: 
 *      - Carlos Eduardo Gonzaga Romaniello de Souza (19.1.4003) 
 *      - Vinicius Gabriel Angelozzi Verona de Resende (19.1.4005)
 * 
*/
int main(int argc, char* argv[]){

    srand(time(NULL));

    // Handle input error
    if (!(argc >= 5 && argc <= 7)){
        help();
    }

    int method = atoi(argv[1]);
    TOTAL_LINES = atoi(argv[2]);
    int sort = atoi(argv[3]);
    int key = atoi(argv[4]);
    char randKey[10] = "";
        
    if (argc == 6){
        char* verbose = argv[5]; 
        if (strcmp(verbose, "-P") == 0){
            VERBOSE = true;
        }
        else{
            strcpy(randKey, argv[5]);
        }
    }
    if (argc == 7){
        char* verbose = argv[5]; 
        strcmp(verbose, "-P") == 0 ? VERBOSE = true : 0;
        strcpy(randKey, argv[6]);
    }


    FILE* input;
    Regs* registry = constructorRegs();

    TNo* bin = criaTNo();
    TItem* item = criaTItem();
    setBinKeyItem(item, key);

    TipoApontador arvore = criaPagina();
    TipoRegistro* reg = constructorTipoRegistro();

    Page* bsTree = constructorBStarPage();
    BStarReg* bsReg = constructorBStarReg();

    Est* est = criaEst();

    time_t inicio, fim;
    double diff;

    char file[100];

    // Handle search method selected
    switch (method){
        case 1:

            strcpy(file, "../output/ASI/");
            strcat(file, argv[2]);
            strcat(file, ".bin");

            inicio = time(NULL);
            criarArquivoSequencial(file, TOTAL_LINES, sort, est);  
            fim = time(NULL);
            diff = difftime(fim, inicio);
            setTempoC(est, diff);

            input = fopen(file, "rb");    

            // Search item
            setKey(registry, key);
            inicio = time(NULL);
            sequentialSearch(registry, input, est);
            fim = time(NULL);
            setTempoP(est, difftime(fim, inicio));

            // Display item
            if (getIndividualIData(registry) != -1){
                printf("\n----------- Item -----------\n");
                printf("| KEY    : %d\n", getIndividualKey(registry));
                printf("| DATA I : %ld\n", getIndividualIData(registry));
                printf("| DATA II: %s\n", getIndividualSData(registry));
                printf("----------------------------\n\n");
            } else{
                puts("\nItem nao encontrado!");
            }

            break;
        case 2:

            strcpy(file, "../output/BinTree/");
            strcat(file, argv[2]);
            strcat(file, ".bin");

            inicio = time(NULL);
            criarArqBinTree(file, TOTAL_LINES, sort, est); 
            fim = time(NULL);
            diff = difftime(fim, inicio);
            setTempoC(est, diff);

            input = fopen(file, "rb"); 
            fread(bin, sizeof(TNo), 1, input);
            incrementaFreadP(est);

            // Search Item
            if (VERBOSE){
                printf("Analisando chaves: ");
            }
            inicio = time(NULL);
            searchBinaryTree(bin, item, input, est);
            fim = time(NULL);
            setTempoP(est, difftime(fim, inicio));
            
            // Display item
            if (item->iData != -1){
                printf("\n----------- Item -----------\n");
                printf("| KEY    : %d\n", item->key);
                printf("| DATA I : %ld\n", item->iData);
                printf("| DATA II: %s\n", item->sData);
                printf("----------------------------\n\n");
            } else{
                puts("\nItem nao encontrado!");
            }

            liberaTNo(bin);
            liberaTItem(item);
            fclose(input);
            break;

        case 3:

            strcpy(file, "../output/BTree/");
            strcat(file, argv[2]);
            strcat(file, ".bin");

            inicio = time(NULL);
            criarArqBTree(file, TOTAL_LINES, sort, key, est);
            fim = time(NULL);
            diff = difftime(fim, inicio);
            setTempoC(est, diff);

            input = fopen(file, "rb");
            setChave(reg, key);
            
            // Le raiz
            if (VERBOSE){
                printf("Analisando chaves: ");
            }

            fread(arvore, sizeofBTree(), 1, input);            
            incrementaFreadP(est);

            inicio = time(NULL);
            searchBTree(reg, input, arvore, est);
            fim = time(NULL);
            setTempoP(est, difftime(fim, inicio));

            // Display item
            if (getDadoInteiro(reg) != -1){
                printf("\n----------- Item -----------\n");
                printf("| KEY    : %d\n", getChave(reg));
                printf("| DATA I : %ld\n", getDadoInteiro(reg));
                printf("| DATA II: %s\n", getDadoString(reg));
                printf("----------------------------\n\n");
            } else{
                puts("\nItem nao encontrado!");
            }

            freeTipoRegistro(reg);
            free(arvore);
            fclose(input);

            break;

        case 4:

            strcpy(file, "../output/BStarTree/");
            strcat(file, argv[2]);
            strcat(file, ".bin");

            inicio = time(NULL);
            criarArqBStarTree(file, TOTAL_LINES, sort, key, est);
            fim = time(NULL);
            diff = difftime(fim, inicio);
            setTempoC(est, diff);

            input = fopen(file, "rb");
            setBSKey(bsReg, key);

            // Le raiz
            if (VERBOSE){
                printf("Analisando chaves: ");
            }

            fread(bsTree, sizeofBSTree(), 1, input);
            incrementaFseekP(est);
            
            inicio = time(NULL);
            searchBSTree(bsTree, bsReg, input, est);
            fim = time(NULL);
            setTempoP(est, difftime(fim, inicio));

            // Display item
            if (getBSIData(bsReg) != -1){
                printf("\n----------- Item -----------\n");
                printf("| KEY    : %d\n", getBSKey(bsReg));
                printf("| DATA I : %ld\n", getBSIData(bsReg));
                printf("| DATA II: %s\n", getBSSData(bsReg));
                printf("----------------------------\n\n");
            } else{
                puts("\nItem nao encontrado!");
            }

            freeBStarReg(bsReg);
            free(bsTree);
            fclose(input);

            break;
            
        default:
            break;
    }

    if (VERBOSE){
        puts("\n--- ESTATISTICAS ---");
        printf("| FwriteC: %d\n", getFwriteC(est));
        printf("| FseekC: %d\n", getFseekC(est));
        printf("| FreadC: %d\n", getFreadC(est));
        printf("| ComparacoesC: %d\n", getComparacoesC(est));
        printf("| TempoC: %lf\n", getTempoC(est));
        printf("\n");
        printf("| FwriteP: %d\n", getFwriteP(est));
        printf("| FseekP: %d\n", getFseekP(est));
        printf("| FreadP: %d\n", getFreadP(est));
        printf("| ComparacoesP: %d\n", getComparacoesP(est));
        printf("| TempoP: %lf\n", getTempoP(est));
        puts("--------------------\n");
    }

    writeStatistics(est, method, TOTAL_LINES, sort, randKey);

    freeEst(est);
    return 0;
        
}

void printaArquivoArvoreBinaria(char* string, int qntd, Est* est){

    FILE* arq = fopen(string, "rb");
    BinTree* bin = constructorBinTree();
    int count = 0;
    int x;
    fread(&x, sizeof(int), 1, arq);

    while (count < qntd) {
        readBinTree(arq, bin, est, 1);
        printf("----------- Item -----------\n");
        printf("| KEY    : %d\n", getIndividualKey(getRegistry(bin)));
        printf("| DATA I : %ld\n", getIndividualIData(getRegistry(bin)));
        printf("| DATA II: %s\n", getIndividualSData(getRegistry(bin)));
        printf("| PEsq   : %d\n", getPEsq(bin));
        printf("| PDir   : %d\n", getPDir(bin));
        printf("| Pos    : %d\n", getPosition(bin));
        printf("----------------------------\n\n");
        count++;
    }
    fclose(arq);
    freeBinTree(bin);

}

void printaArquivoASI(char* string){
    FILE* arq = fopen(string, "rb");

    Regs* reg = constructorRegs();
    while (fread(reg, sizeofReg(), 1, arq) == 1) {
        printf("----------- Item -----------\n");
        printf("| KEY    : %d\n", getIndividualKey(reg));
        printf("| DATA I : %ld\n", getIndividualIData(reg));
        printf("| DATA II: %s\n", getIndividualSData(reg));
        printf("----------------------------\n\n");
    }
    fclose(arq);
    free(reg);
}

/**
 * Displays help menu.
*/
void help(){
        printf("WARNING - O programa deve ser executado com 5 ou 6 parametros!\n\n");
        printf("Sintaxe: ./pesquisa <metodo> <qntd de registros> <ordenacao> <registro> [-P]\n");
        printf("- metodo <1 a 4>    | Acesso sequencial indexado (1), arvore binaria (2), arvore B (3), arvore B* (4).\n");
        printf("- quantidade <int>  | 100, 1000, 10000, 100000, 1000000.\n");
        printf("- ordenacao <1 a 3> | arquivo ordenado ascendentemente (1), arquivo ordenado descendentemente (2), arquivo desordenado (3).\n");
        printf("- registro <int>    | chave do registro a ser pesquisado\n");
        printf("- -P                | habilita print.\n");
}
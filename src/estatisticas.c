#include <stdio.h>
#include <time.h>
#include "estatisticas.h"

Est* criaEst(){
    Est* aux = malloc(sizeof(Est));
    aux->fwriteC = 0;
    aux->fseekC = 0;
    aux->freadC = 0;
    aux->comparacoesC = 0;
    aux->fwriteP = 0;
    aux->fseekP = 0;
    aux->freadP = 0;
    aux->comparacoesP = 0;
    return aux;
}

void freeEst(Est* est){
    free(est);
}

// Gets
int getFwriteC(Est* est){
    return est->fwriteC;
}
int getFseekC(Est* est){
    return est->fseekC;
}
int getFreadC(Est* est){
    return est->freadC;
}
int getComparacoesC(Est* est){
    return est->comparacoesC;
}
double getTempoC(Est* est){
    return est->tempoC;
}
int getFwriteP(Est* est){
    return est->fwriteP;
}
int getFseekP(Est* est){
    return est->fseekP;
}
int getFreadP(Est* est){
    return est->freadP;
}
int getComparacoesP(Est* est){
    return est->comparacoesP;
}
double getTempoP(Est* est){
    return est->tempoP;
}

// Sets
void setFwriteC(Est* est, int x){
    est->fwriteC = x;
}
void setFseekC(Est* est, int x){
    est->fseekC = x;
}
void setFreadC(Est* est, int x){
    est->freadC = x;
}
void setComparacoesC(Est* est, int x){
    est->comparacoesC = x;
}
void setTempoC(Est* est, double x){
    est->tempoC = x;
}
void setFwriteP(Est* est, int x){
    est->fwriteP = x;
}
void setFseekP(Est* est, int x){
    est->fseekP = x;
}
void setFreadP(Est* est, int x){
    est->freadP = x;
}
void setFomparacoesP(Est* est, int x){
    est->comparacoesP = x;
}
void setTempoP(Est* est, double x){
    est->tempoP = x;
}

// Increments
void incrementaFwriteC(Est* est){
    est->fwriteC++;
}
void incrementaFseekC(Est* est){
    est->fseekC++;
}
void incrementaFreadC(Est* est){
    est->freadC++;
}
void incrementaComparacoesC(Est* est){
    est->comparacoesC++;
}
void incrementaFwriteP(Est* est){
    est->fwriteP++;
}
void incrementaFseekP(Est* est){
    est->fseekP++;
}
void incrementaFreadP(Est* est){
    est->freadP++;
}
void incrementaComparacoesP(Est* est){
    est->comparacoesP++;
}

void writeStatistics(Est* est, int metodo, int qntd, int ordenacao, char* chave){

    char file[100] = "";
    
    switch (metodo){
        case 1:
            sprintf(file, "../estatisticas/ASI/asi_%d_%d_%s.txt", qntd, ordenacao, chave);
            break;
        
        case 2:
            sprintf(file, "../estatisticas/BinTree/binTree_%d_%d_%s.txt", qntd, ordenacao, chave);
            break;
        
        case 3:
            sprintf(file, "../estatisticas/BTree/bTree_%d_%d_%s.txt", qntd, ordenacao, chave);
            break;
        
        case 4:
            sprintf(file, "../estatisticas/BStarTree/bStarTree_%d_%d_%s.txt", qntd, ordenacao, chave);
            break;
        
        default:
            break;
    }

    FILE* output = fopen(file, "w");
    fprintf(output, "FwriteC %d\n", getFwriteC(est));
    fprintf(output, "FseekC %d\n", getFseekC(est));
    fprintf(output, "FreadC %d\n", getFreadC(est));
    fprintf(output, "ComparacoesC %d\n", getComparacoesC(est));
    fprintf(output, "TempoC %lf\n", getTempoC(est));
    fprintf(output, "FwriteP %d\n", getFwriteP(est));
    fprintf(output, "FseekP %d\n", getFseekP(est));
    fprintf(output, "FreadP %d\n", getFreadP(est));
    fprintf(output, "ComparacoesP %d\n", getComparacoesP(est));
    fprintf(output, "TempoP %lf", getTempoP(est));
    fclose(output);

}
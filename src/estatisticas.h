#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
extern bool VERBOSE;

typedef struct estatistica{

    // Criacao do arquivo
    int fwriteC;
    int fseekC;
    int freadC;
    int comparacoesC;
    double tempoC;

    // Pesquisa do arquivo
    int fwriteP;
    int fseekP;
    int freadP;
    int comparacoesP;
    double tempoP;

} Est;

// Constructor
Est* criaEst();
void freeEst(Est* est);

// Set
void setFwriteC(Est* est, int x);
void setFseekC(Est* est, int x);
void setFreadC(Est* est, int x);
void setComparacoesC(Est* est, int x);
void setTempoC(Est* est, double x);
void setFwriteP(Est* est, int x);
void setFseekP(Est* est, int x);
void setFreadP(Est* est, int x);
void setComparacoesP(Est* est, int x);
void setTempoP(Est* est, double x);

// Get
int getFwriteC(Est* est);
int getFseekC(Est* est);
int getFreadC(Est* est);
int getComparacoesC(Est* est);
double getTempoC(Est* est);
int getFwriteP(Est* est);
int getFseekP(Est* est);
int getFreadP(Est* est);
int getComparacoesP(Est* est);
double getTempoP(Est* est);

// Increment
void incrementaFwriteC(Est* est);
void incrementaFseekC(Est* est);
void incrementaFreadC(Est* est);
void incrementaComparacoesC(Est* est);
void incrementaFwriteP(Est* est);
void incrementaFseekP(Est* est);
void incrementaFreadP(Est* est);
void incrementaComparacoesP(Est* est);
void writeStatistics(Est* est, int metodo, int qntd, int ordenacao, char* chave);

#endif
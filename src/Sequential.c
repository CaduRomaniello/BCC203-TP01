#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Registry.h"
#include "Sequential.h"
#include "estatisticas.h"

/**
 * Pesquisa em arquivo binário utilizando o método Acesso Sequsncial Indexado e paginação
*/
void sequentialSearch(Regs* reg, FILE* arq, Est* est){

    int qntdPag = TOTAL_LINES / ITENSPAGINA;
    if (TOTAL_LINES % ITENSPAGINA == 0){
        qntdPag = TOTAL_LINES / ITENSPAGINA;
    }
    else{
        qntdPag = (TOTAL_LINES / ITENSPAGINA) + 1;
    }
    int vetPag[qntdPag];

    for (int i = 0; i < qntdPag; i++){
        Regs* aux = constructorRegs();
        fseek(arq, i * (ITENSPAGINA * sizeofReg()), SEEK_SET);
        fread(aux, sizeofReg(), 1, arq);

        incrementaFseekP(est);
        incrementaFreadP(est);

        vetPag[i] = getIndividualKey(aux);
        freeReg(aux);
    }

    Regs vetReg[ITENSPAGINA];
    int pag = 0, qntd_itens;
    long desloc;

    while(pag < qntdPag && vetPag[pag] <= getIndividualKey(reg)){
        pag++;
        incrementaComparacoesP(est);
    }

    if (pag == 0){
        return;
    }
    else{
        if (pag < qntdPag){
            qntd_itens = ITENSPAGINA;
        }
        else{
            fseek(arq, 0, SEEK_END);
            incrementaFseekP(est);

            qntd_itens = (ftell(arq) / sizeofReg()) % ITENSPAGINA;
            if (qntd_itens == 0){
                qntd_itens = ITENSPAGINA;
            }
        }
    }

    desloc = (pag - 1) * ITENSPAGINA * sizeofReg();
    fseek(arq, desloc, SEEK_SET);
    fread(vetReg, sizeofReg(), qntd_itens, arq);

    incrementaFseekP(est);
    incrementaFreadP(est);

    if(VERBOSE){
        printf("Analisando: ");
    }
    for (int i = 0; i < qntd_itens; i++){
        incrementaComparacoesP(est);

        if (getKey(vetReg, i) == getIndividualKey(reg)){
            *reg = vetReg[i];
            return;
        }
        else{
            if(VERBOSE){
                printf("%d ", getKey(vetReg, i));
            }
        }
    }

}
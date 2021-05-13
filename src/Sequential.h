#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include <stdbool.h>
#include "Registry.h"
#include "estatisticas.h"

#define ITENSPAGINA 50
extern int TOTAL_LINES;

void sequentialSearch(Regs* reg, FILE* arq, Est* est);

#endif
extern int TOTAL_LINES;
#include "BTree.h"
#include "BinaryTree.h"
#include "BinTree.h"
#include "BStarTree.h"
#include "estatisticas.h"

void criaString(char* word);
int verificaUsoChave(int* vet, int qntd, int chave);
void criarArquivoSequencial(char* arq, int qntd, int ordenacao, Est* est);
void criarArqBinTree(char* arq, int qntd, int ordenacao, Est* est);
void criarArqBTree(char* arq, int qntd, int ordenacao, int key, Est* est);
void criarArqBStarTree(char* arq, int qntd, int ordenacao, int key, Est* est);
void corrigePonteirosArvoreBinaria(TNo* arvore, int* count);
void corrigePonteiros(TipoPagina* bTree, int* count);
void corrigePonteirosBSTree(Page* bsTree, int* count);
void escreveArvoreBinaria(TNo* arvore, FILE* input, Est* est);
void escreveBTree(TipoPagina* bTree, FILE* input, Est* est);
void escreveBStarTree(Page* bsTree, FILE* input, Est* est);
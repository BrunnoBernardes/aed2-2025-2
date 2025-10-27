#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);

int insere_ArvBin(ArvBin *raiz, int valor);

int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);

int ehAVL(ArvBin *raiz);

#endif

#include <stdio.h>
#include "ArvoreBinaria.h"

int main(){
    ArvBin *raiz = cria_ArvBin();

    insere_ArvBin(raiz, 30);
    insere_ArvBin(raiz, 20);
    insere_ArvBin(raiz, 40);
    insere_ArvBin(raiz, 10);
    insere_ArvBin(raiz, 25);

    printf("Total de nos: %d\n", totalNO_ArvBin(raiz));
    printf("Altura: %d\n", altura_ArvBin(raiz));

    if(ehAVL(raiz))
        printf("A arvore eh AVL\n");
    else
        printf("A arvore NAO eh AVL\n");

    libera_ArvBin(raiz);
    return 0;
}

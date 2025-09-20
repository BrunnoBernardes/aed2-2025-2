/*
* Código retirado e adaptado de: BACKES, André Ricardo. Algoritmos e Estruturas de Dados em C. Rio de Janeiro: LTC, 2023. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++){
        insere_ArvBin(raiz,dados[i]);
        printf("Inserido: %d Tamanho: %d\n",dados[i], totalNO_ArvBin(raiz));
    }

    preOrdem_ArvBin(raiz);
    //emOrdem_ArvBin(raiz);
    //posOrdem_ArvBin(raiz);

    // Aqui pode alterar conforme desejado
    if(remove_ArvBin_rec(raiz,100)){
        printf("No %d foi removido\n", 100);
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO removido\n");

    if(insere_ArvBin_rec(raiz,100)){
        printf("No %d foi inserido\n", 100);
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO inserido\n");
    
    if(remove_ArvBin_iter(raiz,30)){
        printf("No %d foi removido\n", 30);
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO removido\n");
    
    if(insere_ArvBin_rec(raiz,30)){
        printf("No %d foi inserido\n", 30);
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO inserido\n");
        
    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}

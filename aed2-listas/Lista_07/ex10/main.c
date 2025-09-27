/*
* Código retirado e adaptado de: BACKES, André Ricardo. Algoritmos e Estruturas de Dados em C. Rio de Janeiro: LTC, 2023. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

int main(){
    ArvAVL* avl;
    int res,i;
    int N = 8, dados[8] = { 1,2,3,4,7 };
    // OBS.: Tentar usar os exemplos dos slides dos exercícios resolvidos 
    // em sala, como inserção e remoção.

    avl = cria_ArvAVL();

    for(i=0;i<N;i++){
        printf("========================\n");
        printf("Inserindo: %d\n",dados[i]);
        res = insere_ArvAVL(avl,dados[i]);
        printf("\n\nres = %d\n",res);
        // preOrdem_ArvAVL(avl);
        printf("\n\n");
        //system("pause");
    }


    printf("\n=====================\n");

    int NR = 2, dadosR[2] = {2,7};
    for(i=0;i<NR;i++){
        printf("\nRemovendo: %d\n",dadosR[i]);
        res = remove_ArvAVL(avl,dadosR[i]);
        printf("\n\nres = %d\n",res);
        // preOrdem_ArvAVL(avl);
        printf("\n=====================\n");
    }

    libera_ArvAVL(avl);

    return 0;
}

/*
* Código retirado e adaptado de: BACKES, André Ricardo. Algoritmos e Estruturas de Dados em C. Rio de Janeiro: LTC, 2023. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void criaHeap(int *vet, int pai, int fim){
    int aux = vet[pai];
    int filho = 2 * pai + 1;
    while (filho <= fim){
        if(filho < fim){
            if(vet[filho] < vet[filho + 1]){
                filho++;
            }
        }
        if(aux < vet[filho]){
            vet[pai] = vet[filho];
            pai = filho;
            filho = 2 * pai + 1;
        }else{
            filho = fim + 1;
        }
    }
    vet[pai] = aux;
}

void heapSort(int *vet, int N){
    int i, aux;
    for(i=(N - 1)/2; i >= 0; i--){
        criaHeap(vet, i, N-1);
    }
    for (i = N-1; i >= 1; i--){
        aux = vet[0];
        vet [0] = vet [i];
        vet [i] = aux;
        criaHeap(vet, 0, i - 1);
    }
}


int main(){
//==============================================================================
    //int vet[11] = {1,23,4,67,-8,54,90,21,14,-5,1};
    int vet[3] = {23,4,67};
    //int vet[7] = {1,2,3,4,5,6,7};
    int N = 3;

    printf("Sem ordenar:\n");
    //printfVet(vet,N);
    //printfLinha();

    heapSort(vet,N);
    //printfHeap(vet);

    printf("Ordenado:\n");
    //printfVet(vet,N);
//==============================================================================

    system("pause");
    return 0;
}
#include <stdio.h>
#include "max_heap.h"

int main(void) {
    MaxHeap *h = max_heap_criar(10);
    if (!h) {
        printf("Erro ao criar heap\n");
        return 1;
    }

    max_heap_inserir(h, 8);
    max_heap_inserir(h, 3);
    max_heap_inserir(h, 10);
    max_heap_inserir(h, 1);
    max_heap_inserir(h, 6);

    printf("Heap: ");
    max_heap_imprimir(h);

    int chave_removida;
    max_heap_remover(h, &chave_removida);
    printf("Depois de remover o maximo (%d): ", chave_removida);
    max_heap_imprimir(h);
    
    max_heap_destruir(h);
    return 0;
}
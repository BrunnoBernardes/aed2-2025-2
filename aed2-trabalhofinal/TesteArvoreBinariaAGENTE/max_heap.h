#ifndef MAX_HEAP_H
#define MAX_HEAP_H

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} MaxHeap;

MaxHeap *max_heap_criar(int capacidade);
void max_heap_destruir(MaxHeap *h);

int max_heap_inserir(MaxHeap *h, int chave);
int max_heap_remover(MaxHeap *h, int *chave_removida);

void max_heap_imprimir(const MaxHeap *h);

#endif

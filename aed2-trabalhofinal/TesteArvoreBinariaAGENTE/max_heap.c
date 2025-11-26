#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

static void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void max_heapify_para_cima(MaxHeap *h, int i) {
    int pai = (i - 1) / 2;
    if (i > 0 && h->dados[i] > h->dados[pai]) {
        trocar(&h->dados[i], &h->dados[pai]);
        max_heapify_para_cima(h, pai);
    }
}

static void max_heapify_para_baixo(MaxHeap *h, int i) {
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    if (esq < h->tamanho && h->dados[esq] > h->dados[maior]) {
        maior = esq;
    }
    if (dir < h->tamanho && h->dados[dir] > h->dados[maior]) {
        maior = dir;
    }

    if (maior != i) {
        trocar(&h->dados[i], &h->dados[maior]);
        max_heapify_para_baixo(h, maior);
    }
}

MaxHeap *max_heap_criar(int capacidade) {
    MaxHeap *h = malloc(sizeof(MaxHeap));
    if (!h) return NULL;

    h->dados = malloc(capacidade * sizeof(int));
    if (!h->dados) {
        free(h);
        return NULL;
    }

    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

void max_heap_destruir(MaxHeap *h) {
    if (!h) return;
    free(h->dados);
    free(h);
}

int max_heap_inserir(MaxHeap *h, int chave) {
    if (!h || h->tamanho == h->capacidade) {
        return 0; 
    }
    h->dados[h->tamanho] = chave;
    h->tamanho++;
    max_heapify_para_cima(h, h->tamanho - 1);
    return 1;
}

int max_heap_remover(MaxHeap *h, int *chave_removida) {
    if (!h || h->tamanho == 0) {
        return 0;
    }
    *chave_removida = h->dados[0];
    h->dados[0] = h->dados[h->tamanho - 1];
    h->tamanho--;
    max_heapify_para_baixo(h, 0);
    return 1;
}

void max_heap_imprimir(const MaxHeap *h) {
    if (!h) return;
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d ", h->dados[i]);
    }
    printf("\n");
}

#include <stdio.h>
#include "arvore.h"

static void printa(int x) {
    printf("%d ", x);
}

int main(void) {
    Arvore *a = arvore_criar();
    if (!a) {
        printf("Erro ao criar arvore\n");
        return 1;
    }

    arvore_inserir(a, 8);
    arvore_inserir(a, 3);
    arvore_inserir(a, 10);
    arvore_inserir(a, 1);
    arvore_inserir(a, 6);

    printf("Busca 6: %s\n", arvore_buscar(a, 6) ? "sim" : "nao");
    printf("In-ordem: ");
    arvore_em_ordem(a, printa);
    printf("\n");

    arvore_remover(a, 3);
    printf("Depois de remover 3 (in-ordem): ");
    arvore_em_ordem(a, printa);
    printf("\n");

    arvore_destruir(a);
    return 0;
}

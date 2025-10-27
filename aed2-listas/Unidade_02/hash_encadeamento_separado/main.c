#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

// Use "./programa N [TAMANHO_TABELA]" para inserir N números aleatórios sem repetição

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s N [TAMANHO_TABELA]\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int tamanho = (argc >= 3) ? atoi(argv[2]) : TAMANHO_PADRAO_TABELA;

    if (N <= 0 || tamanho <= 0) {
        printf("Erro: valores devem ser positivos.\n");
        return 1;
    }

    TabelaHash* tabela = criarTabela(tamanho);
    if (!tabela) {
        printf("Falha ao criar tabela hash.\n");
        return 1;
    }

    srand(time(NULL));
    int inseridos = 0;

    // Gerar números aleatórios sem repetição
    while (inseridos < N) {
        int numero = rand() % ESPACO_MAX_ALEATORIO;
        if (inserirChave(tabela, numero))
            inseridos++;
    }

    printf("Foram inseridos %d numeros aleatorios sem repeticao.\n", N);
    estatisticasTabela(tabela);

    liberarTabela(tabela);
    return 0;
}
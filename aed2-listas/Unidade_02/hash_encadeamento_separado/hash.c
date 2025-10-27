#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

// Criar tabela hash
TabelaHash* criarTabela(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (!tabela)
        return NULL;

    tabela->tamanho = tamanho;
    tabela->qtd = 0;
    tabela->balde = (No**)calloc(tamanho, sizeof(No*));
    if (!tabela->balde) {
        free(tabela);
        return NULL;
    }
    return tabela;
}

// Liberar memória
void liberarTabela(TabelaHash* tabela) {
    if (!tabela)
        return;
    for (int i = 0; i < tabela->tamanho; i++) {
        No* atual = tabela->balde[i];
        while (atual) {
            No* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(tabela->balde);
    free(tabela);
}

// Buscar chave
int buscarChave(TabelaHash* tabela, int chave) {
    int pos = funcaoHashDivisao(chave, tabela->tamanho);
    No* atual = tabela->balde[pos];
    while (atual) {
        if (atual->chave == chave)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}

// Inserir chave (sem repetição)
int inserirChave(TabelaHash* tabela, int chave) {
    int pos = funcaoHashDivisao(chave, tabela->tamanho);
    No* atual = tabela->balde[pos];

    // evita duplicar número
    while (atual) {
        if (atual->chave == chave)
            return 0;
        atual = atual->proximo;
    }

    No* novo = (No*)malloc(sizeof(No));
    if (!novo)
        return 0;
    novo->chave = chave;
    novo->proximo = tabela->balde[pos];
    tabela->balde[pos] = novo;
    tabela->qtd++;
    return 1;
}

// Remover chave
int removerChave(TabelaHash* tabela, int chave) {
    int pos = funcaoHashDivisao(chave, tabela->tamanho);
    No* atual = tabela->balde[pos];
    No* anterior = NULL;

    while (atual) {
        if (atual->chave == chave) {
            if (anterior) anterior->proximo = atual->proximo;
            else tabela->balde[pos] = atual->proximo;
            free(atual);
            tabela->qtd--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

// Função hash por divisão
int funcaoHashDivisao(int chave, int tamanhoTabela) {
    if (chave < 0) chave = -chave;
    return chave % tamanhoTabela;
}

// Estatísticas simples
void estatisticasTabela(TabelaHash* tabela) {
    int usados = 0, maiorLista = 0;
    long long somaComprimento = 0;

    for (int i = 0; i < tabela->tamanho; i++) {
        int comprimento = 0;
        for (No* atual = tabela->balde[i]; atual; atual = atual->proximo)
            comprimento++;

        if (comprimento > 0) {
            usados++;
            somaComprimento += comprimento;
            if (comprimento > maiorLista)
                maiorLista = comprimento;
        }
    }

    double media = usados ? (double)somaComprimento / usados : 0.0;

    printf("\n--- Estatisticas ---\n");
    printf("Elementos inseridos: %d\n", tabela->qtd);
    printf("Tamanho da tabela:   %d\n", tabela->tamanho);
    printf("Baldes ocupados:     %d\n", usados);
    printf("Maior encadeamento:  %d\n", maiorLista);
    printf("Encadeamento medio:  %.2f\n", media);
}
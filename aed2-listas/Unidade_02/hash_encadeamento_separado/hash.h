#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_PADRAO_TABELA 1031     // número primo para melhor distribuição
#define ESPACO_MAX_ALEATORIO 1000003   // espaço para gerar números aleatórios

// Nó da lista ligada
typedef struct No {
    int chave;
    struct No* proximo;
} No;

// Tabela hash com encadeamento separado
typedef struct {
    int tamanho;   // quantidade de posições (baldes)
    int qtd;       // total de elementos armazenados
    No** balde;    // vetor de ponteiros para listas
} TabelaHash;

// Criação e liberação
TabelaHash* criarTabela(int tamanho);
void liberarTabela(TabelaHash* tabela);

// Operações básicas
int inserirChave(TabelaHash* tabela, int chave);
int buscarChave(TabelaHash* tabela, int chave);
int removerChave(TabelaHash* tabela, int chave);

// Funções auxiliares
int funcaoHashDivisao(int chave, int tamanhoTabela);
void estatisticasTabela(TabelaHash* tabela);

#endif
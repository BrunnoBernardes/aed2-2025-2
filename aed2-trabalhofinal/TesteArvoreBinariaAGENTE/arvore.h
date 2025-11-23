#ifndef ARVORE_H
#define ARVORE_H

typedef struct No {
    int chave;
    struct No *esq;
    struct No *dir;
} No;

typedef struct {
    No *raiz;
} Arvore;

Arvore *arvore_criar(void);
void arvore_destruir(Arvore *a);

int arvore_inserir(Arvore *a, int chave);
int arvore_buscar(const Arvore *a, int chave);
int arvore_remover(Arvore *a, int chave);

void arvore_pre_ordem(const Arvore *a, void (*visitar)(int));
void arvore_em_ordem(const Arvore *a, void (*visitar)(int));
void arvore_pos_ordem(const Arvore *a, void (*visitar)(int));

#endif

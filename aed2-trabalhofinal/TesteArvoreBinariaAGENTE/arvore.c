#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

static No *no_criar(int chave) {
    No *n = malloc(sizeof(No));
    if (!n) return NULL;
    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

Arvore *arvore_criar(void) {
    Arvore *a = malloc(sizeof(Arvore));
    if (!a) return NULL;
    a->raiz = NULL;
    return a;
}

static void no_destruir(No *n) {
    if (!n) return;
    no_destruir(n->esq);
    no_destruir(n->dir);
    free(n);
}

void arvore_destruir(Arvore *a) {
    if (!a) return;
    no_destruir(a->raiz);
    free(a);
}

static No *no_inserir(No *n, int chave, int *ok) {
    if (!n) {
        *ok = 1;
        return no_criar(chave);
    }
    if (chave < n->chave) {
        n->esq = no_inserir(n->esq, chave, ok);
    } else if (chave > n->chave) {
        n->dir = no_inserir(n->dir, chave, ok);
    } else {
        *ok = 0; /* chave duplicada */
    }
    return n;
}

int arvore_inserir(Arvore *a, int chave) {
    if (!a) return 0;
    int ok = 0;
    a->raiz = no_inserir(a->raiz, chave, &ok);
    return ok;
}

int arvore_buscar(const Arvore *a, int chave) {
    No *n = a ? a->raiz : NULL;
    while (n) {
        if (chave == n->chave) return 1;
        n = (chave < n->chave) ? n->esq : n->dir;
    }
    return 0;
}

static No *no_minimo(No *n) {
    while (n && n->esq) n = n->esq;
    return n;
}

static No *no_remover(No *n, int chave, int *ok) {
    if (!n) return NULL;
    if (chave < n->chave) {
        n->esq = no_remover(n->esq, chave, ok);
    } else if (chave > n->chave) {
        n->dir = no_remover(n->dir, chave, ok);
    } else {
        *ok = 1;
        if (!n->esq) {
            No *dir = n->dir;
            free(n);
            return dir;
        } else if (!n->dir) {
            No *esq = n->esq;
            free(n);
            return esq;
        }
        No *m = no_minimo(n->dir);
        n->chave = m->chave;
        n->dir = no_remover(n->dir, m->chave, ok);
    }
    return n;
}

int arvore_remover(Arvore *a, int chave) {
    if (!a) return 0;
    int ok = 0;
    a->raiz = no_remover(a->raiz, chave, &ok);
    return ok;
}

static void no_pre_ordem(const No *n, void (*visitar)(int)) {
    if (!n) return;
    visitar(n->chave);
    no_pre_ordem(n->esq, visitar);
    no_pre_ordem(n->dir, visitar);
}

static void no_em_ordem(const No *n, void (*visitar)(int)) {
    if (!n) return;
    no_em_ordem(n->esq, visitar);
    visitar(n->chave);
    no_em_ordem(n->dir, visitar);
}

static void no_pos_ordem(const No *n, void (*visitar)(int)) {
    if (!n) return;
    no_pos_ordem(n->esq, visitar);
    no_pos_ordem(n->dir, visitar);
    visitar(n->chave);
}

void arvore_pre_ordem(const Arvore *a, void (*visitar)(int)) {
    no_pre_ordem(a ? a->raiz : NULL, visitar);
}

void arvore_em_ordem(const Arvore *a, void (*visitar)(int)) {
    no_em_ordem(a ? a->raiz : NULL, visitar);
}

void arvore_pos_ordem(const Arvore *a, void (*visitar)(int)) {
    no_pos_ordem(a ? a->raiz : NULL, visitar);
}

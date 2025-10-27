#include <stdio.h>
#include <stdlib.h>
#include "ex05.h"

struct NO {
    int chave;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

static void libera_NO(struct NO* no){
    if(no == NULL) return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

void libera_ArvBin(ArvBin *raiz){
    if(raiz == NULL) return;
    libera_NO(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL) return 0;

    struct NO *novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL) return 0;

    novo->chave = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    if(*raiz == NULL){
        *raiz = novo;
    } else {
        struct NO *atual = *raiz;
        struct NO *ant = NULL;

        while(atual != NULL){
            ant = atual;
            if(valor == atual->chave){
                free(novo);
                return 0;
            }
            if(valor < atual->chave)
                atual = atual->esq;
            else
                atual = atual->dir;
        }

        if(valor < ant->chave)
            ant->esq = novo;
        else
            ant->dir = novo;
    }
    return 1;
}

int altura_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;

    int h_esq = altura_ArvBin(&((*raiz)->esq));
    int h_dir = altura_ArvBin(&((*raiz)->dir));

    return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;
    return 1 + totalNO_ArvBin(&((*raiz)->esq)) + totalNO_ArvBin(&((*raiz)->dir));
}

static int ehAVL_NO(struct NO* no, int *altura){
    if(no == NULL){
        *altura = 0;
        return 1;
    }

    int h_esq, h_dir;
    if(!ehAVL_NO(no->esq, &h_esq)) return 0;
    if(!ehAVL_NO(no->dir, &h_dir)) return 0;

    *altura = (h_esq > h_dir ? h_esq : h_dir) + 1;

    int fb = h_esq - h_dir;
    if(fb < -1 || fb > 1)
        return 0;

    return 1;
}

int ehAVL(ArvBin *raiz){
    if(raiz == NULL) return 1;
    int h = 0;
    return ehAVL_NO(*raiz, &h);
}

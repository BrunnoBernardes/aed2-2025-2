/*
* Código retirado e adaptado de: BACKES, André Ricardo. Algoritmos e Estruturas de Dados em C. Rio de Janeiro: LTC, 2023. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" 

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int insere_ArvBin_rec(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL){
        struct NO* novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->info = valor;
        novo->esq = novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    if(valor == (*raiz)->info){
        /* evita duplicados*/
        return 0;
    }else if(valor < (*raiz)->info){
        return insere_ArvBin_rec(&(*raiz)->esq, valor);
    }else{
        return insere_ArvBin_rec(&(*raiz)->dir, valor);
    }
}

static struct NO* menor_no(struct NO* no){
    while(no != NULL && no->esq != NULL)
        no = no->esq;
    return no;
}

static struct NO* remove_rec_no(struct NO* no, int valor, int *ok){
    if(no == NULL)
        return NULL;

    if(valor < no->info){
        no->esq = remove_rec_no(no->esq, valor, ok);
    }else if(valor > no->info){
        no->dir = remove_rec_no(no->dir, valor, ok);
    }else{
        /* Encontrou */
        *ok = 1;
        if(no->esq == NULL){
            struct NO* dir = no->dir;
            free(no);
            return dir;
        }else if(no->dir == NULL){
            struct NO* esq = no->esq;
            free(no);
            return esq;
        }else{
            /* dois filhos: substituir pelo sucessor */
            struct NO* suc = menor_no(no->dir);
            no->info = suc->info;
            no->dir = remove_rec_no(no->dir, suc->info, ok);
        }
    }
    return no;
}

int remove_ArvBin_rec(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    int ok = 0;
    *raiz = remove_rec_no(*raiz, valor, &ok);
    return ok;
}

int remove_ArvBin_iter(ArvBin *raiz, int valor){
    if(raiz == NULL || *raiz == NULL)
        return 0;

    struct NO *pai = NULL, *atual = *raiz;

    /* 1) buscar o nó e manter o ponteiro para o pai */
    while(atual != NULL && atual->info != valor){
        pai = atual;
        if(valor < atual->info) atual = atual->esq;
        else atual = atual->dir;
    }
    if(atual == NULL) return 0; /* não achou */

    /* Caso: dois filhos -> substituir por sucessor in-order */
    if(atual->esq != NULL && atual->dir != NULL){
        /* achar o sucessor (menor da subárvore direita) */
        struct NO *ps = atual, *suc = atual->dir;
        while(suc->esq != NULL){
            ps = suc;
            suc = suc->esq;
        }
        /* copiar valor do sucessor para o nó atual */
        atual->info = suc->info;
        /* agora remover o sucessor (que tem no máx 1 filho à direita) */
        pai = ps;
        atual = suc;
    }

    /* Agora atual tem no máximo 1 filho */
    struct NO* filho;
    if(atual->esq != NULL){
        filho = atual->esq;
    }else{
        filho = atual->dir;
    }

    if(pai == NULL){
        /* removendo a raiz */
        *raiz = filho;
    }else if(pai->esq == atual){
        pai->esq = filho;
    }else{
        pai->dir = filho;
    }

    free(atual);
    return 1;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

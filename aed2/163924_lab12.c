#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    struct no *dir;
    struct no *esq;
    int chave;
    int altura;
}no;

typedef struct arv{
    no *raiz;
}arv;

arv *inicializa_arvore(void);
no *inserir_arvore(no *raiz, int chave);
no *buscar(no *raiz, int chave);
no *remover(no *raiz, int chave);
no *ll(no *x);
no *rr(no *x);
no *rl(no *x);
no *lr(no *x);
void liberar_arvore(no *raiz);
void imprimir_altura(no *raiz);


int main(){
    arv *a = inicializa_arvore();

    int chave = 0;
    while (scanf("%d", &chave) && chave != -1) {
        a->raiz = inserir_arvore(a->raiz, chave);
    }
    imprimir_altura(a->raiz);

    int busca = 0;
    while (scanf("%d", &chave) && chave != -1) {
        no *aux = buscar(a->raiz, chave);
        if (aux != NULL) {
            a->raiz = remover(a->raiz, chave);
        } else {
            a->raiz = inserir_arvore(a->raiz, chave);
        }
    }

    int termo;
    scanf("%d", &termo);
    no *buscado = buscar(a->raiz,termo);
        if(buscado != NULL){
            imprimir_altura(buscado);
        }else{
            printf("Valor nao encontrado");
        }

    liberar_arvore(a->raiz);
    free(a);
    return 0;
}

arv *inicializa_arvore(void){
    arv *h = malloc(sizeof(arv));
        if(h == NULL){
            return NULL;
        }
    h->raiz = NULL;
    return h;
}

int altura_no(no *n){
    if(n == NULL){
        return -1;
    }
    return n->altura;
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

void atualiza_altura(no *n){
    n->altura = 1 + max(altura_no(n->esq),altura_no((n->dir)));
}

no *fator_balanceamento(no *n){
    atualiza_altura(n);
     int fator = altura_no(n->esq) - altura_no(n->dir);

     if(fator > 1){
        if(altura_no(n->esq->esq) >= altura_no(n->esq->dir)){
            return ll(n);
        }else{
            return lr(n);
        }
     }else if(fator < -1){
        if(altura_no(n->dir->dir) >= altura_no(n->dir->esq)){
            return rr(n);
        }else{
            return rl(n);
        }
     }
     return n;
}

no *inserir_arvore(no *raiz, int chave){
    if(raiz == NULL){
        no *novo = malloc(sizeof(no));
            if(novo == NULL){
                return NULL;
            }
        novo->chave = chave;
        novo->altura = 0;
        novo->dir = novo->esq = NULL;
        return novo;
    }

    if(chave < raiz->chave){
        raiz->esq = inserir_arvore(raiz->esq,chave);
    }else{
        raiz->dir = inserir_arvore(raiz->dir,chave);
    }
    return fator_balanceamento(raiz);
}

no *buscar(no *raiz, int chave){
    if(raiz == NULL || raiz->chave == chave){
        return raiz;
    }

    if(chave < raiz->chave){
        return buscar(raiz->esq,chave);
    }else{
        return buscar(raiz->dir,chave);
    }
}

no *remover(no *raiz, int chave){
    if(raiz == NULL){
        return NULL;
    }

    if(chave < raiz->chave){
        raiz->esq = remover(raiz->esq,chave);
    }else if(chave > raiz->chave){
        raiz->dir = remover(raiz->dir,chave);
    }else{
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }

        if(raiz->esq == NULL){
            no *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if(raiz->dir == NULL){
            no *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        no *temp = raiz->dir;
        while(temp->esq != NULL){
            temp = temp->esq;
        }
        raiz->chave = temp->chave;
        raiz->dir = remover(raiz->dir,temp->chave);
    }
    return fator_balanceamento(raiz);
}

no *ll(no *x){
    no *y = x->esq;
    x->esq = y->dir;
    y->dir = x;
    atualiza_altura(x);
    atualiza_altura(y);
    return y;
}

no *rr(no *x){
    no *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualiza_altura(x);
    atualiza_altura(y);
    return y;
}

no *rl(no *x){
    x->dir = ll(x->dir);
        return rr(x);
}

no *lr(no *x){
    x->esq = rr(x->esq);
        return ll(x);
}

void imprimir_altura(no *raiz){
    printf("%d,%d,%d\n",raiz->altura,altura_no(raiz->esq),altura_no(raiz->dir));
}

void liberar_arvore(no *raiz){
    if(raiz != NULL){
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz);
    }
}
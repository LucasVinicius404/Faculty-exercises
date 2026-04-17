#include <stdio.h>
#include <stdlib.h>

typedef struct arv{
    int info;
    int altura;
    struct arv *dir;
    struct arv *esq;
}no;

no *buscar(no *raiz, int n);
no *insere(no *raiz, int chave);
no *remover(no *raiz, int chave);
no *minimun(no *raiz);
void emOrdem(no *raiz);




int altura(no *raiz){
    if(raiz == NULL){
        return 0;
    }
    return raiz->altura;
}

int max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

void atualiza_alt(no *raiz){
    if(raiz != NULL){
        raiz->altura =  1 + max(altura(raiz->esq),altura(raiz->dir));
    }
}

int fator_balanceamento(no *raiz){
    if(raiz == NULL){
        return 0;
    }
    return (altura(raiz->esq) - altura(raiz->dir));
}



no *ll(no *x){
    no *y = x->esq;
    x->esq = y->dir;
    y->dir = x;
    atualiza_alt(x);
    atualiza_alt(y);
    return y;
}

no *rr(no *x){
    no *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualiza_alt(x);
    atualiza_alt(y);
    return y;
}

no *lr(no *x){
    x->esq = rr(x->esq);
    return ll(x);
}

no *rl(no *x){
    x->dir = ll(x->dir);
    return rr(x);
}


int main(){
    no *raiz = NULL;

    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = 6;

    for(int i = 0; i < n; i++){
        raiz = insere(raiz, valores[i]);
    }

    printf("Arvore em ordem apos insercoes:\n");
    emOrdem(raiz);
    printf("\n");

    // 🔍 Busca
    int chave = 25;
    no *res = buscar(raiz, chave);

    if(res != NULL){
        printf("Achou %d\n", chave);
    }else{
        printf("Nao achou %d\n", chave);
    }

    printf("\nRemovendo 40...\n");
    raiz = remover(raiz, 40);

    emOrdem(raiz);
    printf("\n");

    printf("\nRemovendo 30...\n");
    raiz = remover(raiz, 30);

    emOrdem(raiz);
    printf("\n");

    printf("\nRemovendo 10...\n");
    raiz = remover(raiz, 10);

    emOrdem(raiz);
    printf("\n");

    return 0;
}

no *buscar(no *raiz, int n){
    if(raiz == NULL){
        return NULL;
    }
    
    if(raiz->info == n){
        return raiz;
    }else if(raiz->info < n){
        return buscar(raiz->dir,n);
    }else{
        return buscar(raiz->esq,n);
    }
}

no *insere(no *raiz, int chave){
    if(raiz == NULL){
        no *novo = malloc(sizeof(no));
            if(novo == NULL){
                return NULL;
            }
        novo->info = chave;
        novo->altura = 1;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    
    if(chave > raiz->info){
        raiz->dir = insere(raiz->dir,chave);
    }else{
        raiz->esq = insere(raiz->esq,chave);
    }
    
    atualiza_alt(raiz);
    
    int fb = fator_balanceamento(raiz);
    
    if(fb > 1 && chave < raiz->esq->info){
        return ll(raiz);
    }
    
    if(fb < -1 && chave > raiz->dir->info){
        return rr(raiz);
    }
    
    if(fb > 1 && chave > raiz->esq->info){
        return lr(raiz);
    }
    
    if(fb < -1 && chave < raiz->dir->info){
        return rl(raiz);
    }
    
    return raiz;
}

no *remover(no *raiz, int chave){
    if(raiz == NULL)
        return NULL;

    // 🔍 BUSCA
    if(chave < raiz->info)
        raiz->esq = remover(raiz->esq, chave);
    else if(chave > raiz->info)
        raiz->dir = remover(raiz->dir, chave);
    else{
        // NÓ ENCONTRADO

        // 0 ou 1 filho
        if(raiz->esq == NULL || raiz->dir == NULL){
            no *temp = raiz->esq ? raiz->esq : raiz->dir;

            if(temp == NULL){
                free(raiz);
                return NULL;
            }else{
                *raiz = *temp;
                free(temp);
            }
        }
        // 2 filhos
        else{
            no *temp = minimun(raiz->dir);
            raiz->info = temp->info;
            raiz->dir = remover(raiz->dir, temp->info);
        }
    }

    // ATUALIZA ALTURA
    atualiza_alt(raiz);

    // FATOR DE BALANCEAMENTO
    int fb = fator_balanceamento(raiz);

    // CASOS DE ROTAÇÃO

    // LL
    if(fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        return ll(raiz);

    // LR
    if(fb > 1 && fator_balanceamento(raiz->esq) < 0)
        return lr(raiz);

    // RR
    if(fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rr(raiz);

    // RL
    if(fb < -1 && fator_balanceamento(raiz->dir) > 0)
        return rl(raiz);

    return raiz;
}
no *minimun(no *raiz){
    while(raiz->esq != NULL){
        raiz = raiz->esq;
    }
    return raiz;
}

void emOrdem(no *raiz){
    if(raiz != NULL){
        emOrdem(raiz->esq);
        printf("%d (h=%d) ", raiz->info, raiz->altura);
        emOrdem(raiz->dir);
    }
}
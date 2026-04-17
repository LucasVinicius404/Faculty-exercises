#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    struct no *prox;
    int id;
    int prioridade;
}no;

typedef struct lista{
    no *cabeca;
    int tam;
}lista;


lista *inicializa_lista(void){
    lista *l =malloc(sizeof(lista));
        if(l == NULL){
            return NULL;
        }
    l->cabeca = NULL;
    l->tam = 0;
    return l;
}

void insere_lista(lista *l, int id, int prioridade){
    no *novo = malloc(sizeof(no));
        if(novo == NULL){
            return;
        }
    novo->id = id;
    novo->prioridade = prioridade;
    l->tam = l->tam + 1;
    novo->prox = NULL;
    if(l->cabeca == NULL){
        l->cabeca = novo;
    }else{
        no *aux = l->cabeca;
            while(aux->prox != NULL){
                aux = aux->prox;
            }
        aux->prox = novo;
    }
}

void insertion_list(lista *l, int tam){
    no *cabeca_ordenada  = NULL;

    no *aux = l->cabeca;
    while(aux != NULL){
        no *proximo = aux->prox;

        if(cabeca_ordenada == NULL || aux->prioridade < cabeca_ordenada->prioridade){
            aux->prox = cabeca_ordenada;
            cabeca_ordenada = aux;
        }else{
            no *ant = cabeca_ordenada;

            while(ant->prox !=NULL && ant->prox->prioridade <= aux->prioridade ){
                ant = ant->prox;
            }
            aux->prox = ant->prox;
            ant->prox= aux;
        }
        aux = proximo;
    }
    l->cabeca = cabeca_ordenada;
}

void imprime(lista *l){
    no *imprime = l->cabeca;
    while(imprime != NULL){
        printf("%d %d\n", imprime->id,imprime->prioridade);
        imprime = imprime->prox;
    }
}

void desaloca_lista(lista *l){
    no *aux = l->cabeca;
    while(aux != NULL){
        no *remove = aux;
        aux = aux->prox;
        free(remove);
    }
    free(l);
}


int main(){
    int n;

    scanf("%d", &n);

    lista *l = inicializa_lista();

    for(int i = 0; i < n; i++){
        int id, prioridade;
        scanf("%d %d",&id, &prioridade);
        insere_lista(l,id,prioridade);
    }

    insertion_list(l,n);

    imprime(l);
    desaloca_lista(l);
    return 0;
}
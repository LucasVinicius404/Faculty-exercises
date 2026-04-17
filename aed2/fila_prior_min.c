
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no{
    int chave;
    int id;
}no;

typedef struct fila{
    no *array;
    int capacidade;
    int tam_heap;
}fila;

fila *inicializa_fila(int tam);
void swap(no *a, no *b);
void min_heap_decrease(fila *f, int i, int nova_chave);
void min_heap_insert(fila *f, int id, int chave);
void min_heapfy(fila *f, int i);
int heap_minimun(fila *f);
void min_heap_extract(fila *f);
int left(int i);
int right(int i);
int parent(int i);
void imprime_heap(fila *f);

int main(){
    int tam, m,remocao;
    scanf("%d", &tam);
    fila *f = inicializa_fila(tam);

    for(int i = 0; i < tam; i++){
        int chave, id;
        scanf("%d %d", &chave, &id);
        min_heap_insert(f,id,chave);
    }
    imprime_heap(f);
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        int nova_chave, indice;
        scanf("%d %d", &indice, &nova_chave);
        min_heap_decrease(f,indice,nova_chave);
    }
    imprime_heap(f);
    scanf("%d", &remocao);

    for(int i = 0; i < remocao;i++){
        min_heap_extract(f);
    }
    imprime_heap(f);
    free(f->array);
    free(f);
    return 0;
}

fila *inicializa_fila(int tam){
     fila *f = malloc(sizeof(fila));
        if(f == NULL){
            return NULL;
        }
     f->array = malloc(tam * sizeof(no));
        if(f->array == NULL){
            free(f);
            return NULL;
        }
    f->capacidade = tam;
    f->tam_heap = 0;

    return f;
}

void swap(no *a, no *b){
    no temp = *a;
    *a = *b;
    *b = temp; 
}

void min_heap_decrease(fila *f, int i, int nova_chave){
    if(nova_chave > f->array[i].chave){
        return;
    }
    f->array[i].chave = nova_chave;
    while(i > 0 && f->array[parent(i)].chave > f->array[i].chave){
        swap(&f->array[i],&f->array[parent(i)]);
        i = parent(i);
    }
}

void min_heap_insert(fila *f, int id, int chave){
    if(f->tam_heap == f->capacidade){
        return;
    }
    f->tam_heap++;
    int i = f->tam_heap - 1;

    f->array[i].id = id;
    f->array[i].chave = INT_MAX;

    min_heap_decrease(f,i,chave);
}

void min_heapfy(fila *f, int i){
    int l = left(i), r = right(i);
        int menor = i;
    if(l < f->tam_heap && f->array[l].chave < f->array[menor].chave){
        menor = l;
    }
    if(r < f->tam_heap && f->array[r].chave < f->array[menor].chave){
        menor = r;
    }
    if(menor != i){
        swap(&f->array[i], &f->array[menor]);
        min_heapfy(f,menor);
    }
}
int heap_minimun(fila *f){
    return f->array[0].id;
}

void min_heap_extract(fila *f){
    if(f->tam_heap < 1){
        return;
    }
    swap(&f->array[0], &f->array[f->tam_heap - 1]);
    f->tam_heap--;
    min_heapfy(f,0);
}

int left(int i){
    return (2 * i) + 1;
}

int right(int i){
    return (2 * i) + 2;
}

int parent(int i){
    return (i - 1)/2;
}

void imprime_heap(fila *f){
    for(int i = 0; i <f->tam_heap; i++){
        printf("%d ", f->array[i].id);
    }
    printf("\n");
}

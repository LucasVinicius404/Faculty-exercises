#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para INT_MIN

// --- Estruturas ---
typedef struct no {
    int chave;
    int id;
} no;

typedef struct fila {
    no *array;
    int *vetor_auxiliar;
    int capacidade;
    int tam_heap;
} fila;

// --- Protótipos ---
fila *inicializa_fila(int tam);
void swap(fila *f, int i, int j);
no heap_maximum(fila *f);
no heap_extract_max(fila *f);
void heapfy(fila *f, int i);
void max_heap_insert(fila *f, int id, int chave);
void max_heap_increase(fila *f, int id, int nova_chave);
int left(int i);
int right(int i);
int parent(int i);
void desaloca_fila(fila *f);

// --- Main ---
int main() {
    int tam;
    printf("Digite a capacidade da fila: ");
    scanf("%d", &tam);

    fila *f = inicializa_fila(tam);

    printf("Digite %d pares de (id, chave):\n", tam);
    for (int i = 0; i < tam; i++) {
        int id, chave;
        scanf("%d %d", &id, &chave);
        max_heap_insert(f, id, chave);
    }

    printf("\nExtraindo todos os elementos em ordem de prioridade:\n");
    while (f->tam_heap > 0) {
        no extraido = heap_extract_max(f);
        printf("Elemento removido -> ID: %d, Chave: %d\n", extraido.id, extraido.chave);
    }

    desaloca_fila(f);
    return 0;
}

// --- Implementações ---
fila *inicializa_fila(int tam) {
    fila *f = malloc(sizeof(fila));
    if (f == NULL) return NULL;

    f->array = malloc(tam * sizeof(no));
    if (f->array == NULL) {
        free(f);
        return NULL;
    }

    f->vetor_auxiliar = malloc(tam * sizeof(int));
    if (f->vetor_auxiliar == NULL) {
        free(f->array);
        free(f);
        return NULL;
    }

    f->capacidade = tam;
    f->tam_heap = 0;
    return f;
}

void swap(fila *f, int i, int j) {
    // Atualiza o mapa de posições ANTES de trocar
    int id1 = f->array[i].id;
    int id2 = f->array[j].id;
    f->vetor_auxiliar[id1] = j;
    f->vetor_auxiliar[id2] = i;

    // Troca os elementos no heap
    no temp = f->array[i];
    f->array[i] = f->array[j];
    f->array[j] = temp;
}

void heapfy(fila *f, int i) {
    int l = left(i);
    int r = right(i);
    int maior = i;

    if (l < f->tam_heap && f->array[l].chave > f->array[maior].chave) {
        maior = l;
    }
    if (r < f->tam_heap && f->array[r].chave > f->array[maior].chave) {
        maior = r;
    }

    if (maior != i) {
        swap(f, i, maior);
        heapfy(f, maior);
    }
}

void max_heap_increase(fila *f, int id, int nova_chave) {
    int i = f->vetor_auxiliar[id];
    if (nova_chave < f->array[i].chave) {
        printf("Erro: nova chave eh menor que a chave atual.\n");
        return;
    }
    f->array[i].chave = nova_chave;
    while (i > 0 && f->array[parent(i)].chave < f->array[i].chave) {
        swap(f, i, parent(i));
        i = parent(i);
    }
}

no heap_maximum(fila *f) {
    if (f->tam_heap < 1) {
        printf("Erro: Heap vazio!\n");
        exit(1);
    }
    return f->array[0];
}

no heap_extract_max(fila *f) {
    if (f->tam_heap < 1) {
        printf("Erro: Heap vazio!\n");
        exit(1);
    }
    no max = f->array[0];
    swap(f, 0, f->tam_heap - 1);
    f->tam_heap--;
    heapfy(f, 0);
    return max;
}

void max_heap_insert(fila *f, int id, int chave) {
    if (f->tam_heap == f->capacidade) {
        printf("Erro: Heap cheio!\n");
        return;
    }
    f->tam_heap++;
    int i = f->tam_heap - 1;

    f->array[i].id = id;
    f->array[i].chave = INT_MIN; // Sentinela seguro

    f->vetor_auxiliar[id] = i;

    max_heap_increase(f, id, chave);
}

void desaloca_fila(fila *f) {
    free(f->array);
    free(f->vetor_auxiliar);
    free(f);
}

int parent(int i) { 
    return (i - 1) / 2; 
}
int left(int i) { 
    return (2 * i) + 1; 
}
int right(int i) { 
    return (2 * i) + 2; 
}
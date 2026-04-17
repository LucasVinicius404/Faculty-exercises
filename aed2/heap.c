#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b);
void heap_sort(int *vetor, int ini, int fim, int tam);
void build_max_heap(int *vetor, int tam);
void heapfy(int *vetor, int indice,int tam);

int main(){
     int n;

    scanf("%d", &n);

    int *vetor = malloc(n * sizeof(int));
        if(vetor == NULL){
            return 1;
        }
    
    for(int i = 0;  i < n; i++){
        scanf("%d", &vetor[i]);
    }
    printf("a sequencia desordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");

    heap_sort(vetor,0,n-1,n);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}

void swap(int *a,int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void build_max_heap(int *vetor, int tam){
    for(int i = (tam/2)+ 1; i >= 0; i--){
        heapfy(vetor,tam,i);
    }
}

void heapfy(int *vetor,int tam, int indice){
    int l = (2*indice) + 1, r = (2 * indice)+2;
    int maior = indice;
        if(l < tam && vetor[l] > vetor[maior]){
            maior = l;
        }
        if(r < tam && vetor[r] > vetor[maior]){
            maior  = r;
        }
    if(maior != indice){
        swap(&vetor[indice],&vetor[maior]);
        heapfy(vetor,tam,maior);
    }
}

void heap_sort(int *vetor, int ini, int fim, int tam){
    build_max_heap(vetor,tam);
    for(int i = tam - 1; i > 0; i--){
        swap(&vetor[0],&vetor[i]);
        heapfy(vetor,i,0);
    }
}
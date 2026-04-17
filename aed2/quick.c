#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *vetor, int ini,int fim);
int partition(int *vetor, int ini, int fim);
void swap(int *a, int *b);

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

    quick_sort(vetor,0,n-1);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }
    free(vetor);
    return 0;
}

void quick_sort(int *vetor, int ini,int fim){
    if(ini < fim){
        int q = partition(vetor,ini,fim);
        quick_sort(vetor,ini,q - 1);
        quick_sort(vetor,q + 1,fim);
    }
}
int partition(int *vetor, int ini, int fim){
    int chave = vetor[fim];
    int i = ini - 1;
    
    for(int j = ini; j <= fim; j++){
        if(vetor[j] <= chave){
            i++;
            swap(&vetor[j],&vetor[i]);
        }
    }
    swap(&vetor[i + 1],&vetor[fim]);
    return i + 1;
}

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
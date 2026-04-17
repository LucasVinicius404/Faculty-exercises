#include <stdio.h>
#include <stdlib.h>

void selection_Sort(int *vetor, int tam);
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

    selection_Sort(vetor,n);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }
}
void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void selection_Sort(int *vetor, int tam){
    for(int i = 0; i < tam; i++){
        int menor = i;
        for(int j = i + 1 ; j < tam; j++){
            if(vetor[j] < vetor[menor]){
                menor = j;
            }
        }
        swap(&vetor[i], &vetor[menor]);
    }
}
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *vetor, int tam);
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

    bubble_sort(vetor,n);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int *vetor, int tam){
    int trocou = 0;
    for(int i = 0; i < tam - 1; i++){
        trocou = 0;
        for(int j = 0; j < (tam - i)- 1; j++){
            if(vetor[j] > vetor[ j + 1]){
                swap(&vetor[j],&vetor[j+1]);
                trocou = 1;
            }
        }
        if(!trocou){
            break;
        }
    }
}

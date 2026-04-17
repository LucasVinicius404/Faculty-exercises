#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *vetor, int tam);

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

    insertion_sort(vetor,n);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}

void insertion_sort(int *vetor, int tam){
    for(int i = 1; i < tam; i++){
        int chave = vetor[i];
        int j = i - 1;
        while(j >= 0 && chave < vetor[j]){
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}
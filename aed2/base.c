#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
void merge(int *vetor, int ini, int meio, int fim){
    int m1 = (meio - ini)+ 1;
    int m2 = fim - meio;

    int *vet1 = ((m1 + 1) * sizeof(int));
    int *vet2 = ((m2 + 1) * sizeof(int));

    for(int i = 0; i < m1; i++){
        vet1[i] = vetor[i];
    }
    for(int i = 0; i < m2; i++){
        vet2[i] = vetor[meio + 1 + i];
    }
    for(int i = 0; i < tam;i++){
        
    }
}

void merge_sort(int *vetor, int ini, int fim){
    if(ini >= fim){
        return NULL;
    }
    int meio = (fim - ini) / 2;
    merge_sort(vetor,ini,meio);
    merge_sort(vetor,meio + 1,fim);
    merge(vetor,ini,meio,fim);
}


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

    quick_sort(vetor,0,n);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *vetor, int ini, int tam);
void merge(int *vetor, int ini, int meio, int fim);

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

    merge_sort(vetor,0,n - 1);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }
    free(vetor);
    return 0;
}

void merge_sort(int *vetor, int ini, int tam){
    if(ini >= tam){
        return;
    }
    int meio = (ini + tam) / 2;

    merge_sort(vetor,ini,meio);
    merge_sort(vetor,meio + 1,tam);
    merge(vetor,ini,meio,tam);
}

void merge(int *vetor, int ini, int meio, int fim){
    int m1 = (meio - ini) + 1;
    int m2 = fim - meio;

    int *vet1 = malloc((m1 + 1) * sizeof(int));
        if(vet1 == NULL){
            return;
        }
    int *vet2 = malloc((m2 + 1) * sizeof(int));
        if(vet2 == NULL){
            return;
        }
    for(int i = 0; i < m1;i++){
        vet1[i] = vetor[ini + i]; 
    }
    for(int j = 0; j < m2;j++){
        vet2[j] = vetor[meio + 1 + j];
    }
    vet1[m1] = 100000;
    vet2[m2] = 100000;

    int i = 0, j = 0,k=0;
    for(int k = ini; k <= fim;k++){
        if(vet1[i] <= vet2[j]){
            vetor[k] = vet1[i];
            i++;
        }else{
            vetor[k] = vet2[j];
            j++;
        }
    }

    free(vet1);
    free(vet2);
}
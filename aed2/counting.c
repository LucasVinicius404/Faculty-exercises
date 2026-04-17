#include <stdio.h>
#include <stdlib.h>

void counting_sort(int *vetor, int tam, int maior);

int main(){
    int n;

    scanf("%d", &n);

    int *vetor = malloc(n * sizeof(int));
        if(vetor == NULL){
            return 1;
        }
    int maior = 0;
    for(int i = 0;  i < n; i++){
        scanf("%d", &vetor[i]);
        if(maior < vetor[i]){
            maior = vetor[i];
        }
    }
    printf("a sequencia desordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");

    counting_sort(vetor,n,maior);
    printf("a sequencia ordenada é: ");
    for(int i = 0;  i < n; i++){
        printf("%d ", vetor[i]);
    }

    free(vetor);
    return 0;
}

void counting_sort(int *vetor, int tam, int maior){
    int *b = malloc(tam * sizeof(int));
    int *c = calloc(maior+1,sizeof(int));

    for(int i = 0; i < tam; i++){
        c[vetor[i]]++;
    }
    for(int i = 1; i <= maior; i++){
        c[i] += c[i-1];
    }
    for(int j = tam - 1; j >= 0;j--){
        b[c[vetor[j]] - 1] = vetor[j];
        c[vetor[j]]--;
    }
    for(int i = 0;  i < tam; i++){
        vetor[i] = b[i];
    }
    free(c);
    free(b);
}


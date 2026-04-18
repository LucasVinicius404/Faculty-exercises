#include <stdio.h>
#include <stdlib.h>

void inter_balanceada(int *vetor, int registros, int quant_fitas, int memo_tam);
int compare_int(const void *a, const void *b);

int main(){
    int regs, num_fitas, tam_memo;

    scanf("%d", &regs);

    int *vetor = malloc(regs * sizeof(int));
        if(vetor == NULL){
            return 1;
        }
    
    for(int i = 0; i < regs; i++){
        scanf("%d", &vetor[i]);
    }

    scanf("%d", &num_fitas);
    scanf("%d", &tam_memo);

    inter_balanceada(vetor,regs,num_fitas,tam_memo);

    free(vetor);
    return 0;
}

int compare_int(const void *a, const void *b){
    //(int*)a faz com que o que era void vire int o * na frente diz que é a diferença ao fazer a - b o resultado negativo o compilador entedende com a menor se positivo b menor
    return (*(int*)a - *(int *)b);
}   

void inter_balanceada(int *vetor, int registros, int quant_fitas, int memo_tam){
    int **fitas = malloc(quant_fitas * sizeof(int*));
        if(fitas == NULL){
            return;
        }
    for(int i = 0; i < quant_fitas;i++){
        fitas[i] = malloc(registros * sizeof(int));
    }

    int *memoria = malloc(memo_tam * sizeof(int));
        if(memoria == NULL){
            return;
        }
    int *freq_fita = calloc(quant_fitas,sizeof(int));

    int f = 0,fita_atual = 0;

    while(f < registros){
        int bloco_atual = 0;
        for(int i = 0; i < memo_tam; i++){
            if(f < registros){
                memoria[i] = vetor[f];
                f++;
                bloco_atual++;
            }
    }
    qsort(memoria,bloco_atual,sizeof(int),compare_int);

    for(int i = 0; i < bloco_atual; i++){
        fitas[fita_atual][freq_fita[fita_atual]] = memoria[i];
        freq_fita[fita_atual]++;
    }
    fita_atual = (fita_atual + 1) % quant_fitas;
}
    int impressão = 0;
    while(impressão < quant_fitas){
        printf("Fita %d:", impressão+1);
        for(int i = 0;i < freq_fita[impressão]; i++){
            printf(" %d", fitas[impressão][i]);
        }
        printf("\n");
        impressão++;
    }
    for(int i = 0; i < quant_fitas; i++){
        free(fitas[i]);
    }
    free(fitas);
    free(memoria);
    free(freq_fita);
}


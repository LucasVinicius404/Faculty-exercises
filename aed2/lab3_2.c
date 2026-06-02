#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char *fita);
void insert(int *vetor, char *fita);
void find(int *vet, char *fita);

int main(){
    /*
    Função main tem a função de controle do usuario

    vetor iniciado em 1.400.000 para evitar estouro do vetor em caso de fitas grande e de grande peso

    o usuario escreve a quantidade de operações com um limie de 1 milhão

    em cada operação o usuario manda

    operação fita

    operações validas:

    insert fita

        ou

    find fita

    */
    int ops;
    int *vetor = calloc(1400000, sizeof(int));
    scanf("%d ", &ops);

    for (int i = 0; i < ops; i++){
        char operacao[7];
        char fita[11];

        scanf(" %s %s", operacao, fita);
        if (operacao[0] == 'i'){
            insert(vetor, fita);
        }
        else if (operacao[0] == 'f'){
            find(vetor, fita);
        }
    }

    free(vetor);
    return 0;
}

int hash(char *fita){

    /*
        função hash recebe a fita dada e calcula seu tamanho

        dando um valor aos nucleotidios

        A = 1
        C = 2
        G = 3
        T = 4


        a soma começa em zero, para cada passagem da soma ela é multiplicada na base 4 e somada com o valor do nucleotidio

        por fim retorna o indice evitando colisão
    */
    int soma = 0;
    int tam = strlen(fita);

    for (int i = 0; i < tam; i++){
        int valor_nucl;
        if (fita[i] == 'A')
            valor_nucl = 1;
        else if (fita[i] == 'C')
            valor_nucl = 2;
        else if (fita[i] == 'G')
            valor_nucl = 3;
        else if (fita[i] == 'T')
            valor_nucl = 4;

        soma = (soma * 4) + valor_nucl;
    }

    return soma;
}

void insert(int *vetor, char *fita){
    /*
    chama a função hash para encontrar o id referente a fita dada, retorna o indice e marca no vetor como 1
    para mostrar que ela foi adicionada

    para o desafio de vez marcar como 1 eu somaria para marcar a frequencia que a fita aparece

    vetor[id] += 1;
    */
    int id = hash(fita);
    vetor[id] = 1;
}

void find(int *vet, char *fita){
    /*
        chama função hash e veifica no vetor se está marcado com 1

        caso esteja quer dizer que a fita foi encontrada


        para o desafio bonus o bloco de if ficaria

        if(vet[id] == 0){
            printf("n\n");
        }else{
            printf("a fita %s aparece %d vezes \n", fita,vet[id]);
        }
    */
    int id = hash(fita);

    if (vet[id] == 1){
        printf("y\n");
    }
    else{
        printf("n\n");
    }
}
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    int palavra_valida(char *palavra);
    int compara_string(char *str1, char *str2);
    void swap(char **a, char **b);
    void max_heapfy(char *vetor[], int tam, int i);
    void build_max_heap(char *vetor[], int M);
    void heapSort(char *vetor[], int M);
     
    int main(){
        int N,M;
     
            scanf("%d", &N);
        //criação de um array que recebera termos char
        char **vetor = malloc(N * sizeof(char *));
            if(vetor == NULL){
                return 1;
            }
        for(int i = 0; i < N; i++){
            char buffer[21];
            //recebimento da palavra completa até 20 caracteres
            scanf("%s", buffer);
            //manda para função que verifica se ela está no intervalo de 'a' a 'z'
            if(!palavra_valida(buffer)){
                printf("a palavra %s eh invalida",buffer);
                for (int j = 0; j < i; j++) {
                    free(vetor[j]);
                }
                free(vetor);
                return 0;
            }
            //aloca no vetor o tamanho exato da palavra mais o '\0'
            vetor[i] = malloc(strlen(buffer) + 1);
                if(vetor[i] == NULL){
                    for (int j = 0; j < i; j++) {
                    free(vetor[j]);
                }
                    free(vetor);
                    return 0;
                }
            //copia a palavra para o vetor
            strcpy(vetor[i],buffer);
        }
        scanf("%d", &M);
        //cria outro vetor
        char **vetor_selecionado = malloc(M * sizeof(char*));
            if(vetor_selecionado == NULL){
                for (int j = 0; j < N; j++) {
                    free(vetor[j]);
                }
                free(vetor);
                return 1;
            }
        for(int i = 0; i < M; i++){
            int indice;
            //copia-se o endereço do vetor original e coloca no vetor novo
            scanf("%d", &indice);
            vetor_selecionado[i] = vetor[indice];
        }
        heapSort(vetor_selecionado,M);
     
        for(int i = 0; i < N; i++){
            free(vetor[i]);
        }
        free(vetor);
        free(vetor_selecionado);
        return 0;   
    }
     //troca de ponteiro
    void swap(char **a, char **b){
        char *temp = *a;
        *a = *b;
        *b = temp;
    }
     
    int compara_string(char *str1, char *str2){
        while(*str1 && *str1 == *str2){
            str1++;
            str2++;
        }
        //retorna a diferença de ascll das duas strings se mandar 0 é pq são iguais
        return *str1 - *str2;
    }
     
    int palavra_valida(char *palavra){
        int i = 0;
        while(palavra[i] != '\0'){
            if(palavra[i] < 'a' || palavra[i] > 'z'){
                return 0;
            }
            i++;
        }
        return 1;
    }
     
    void heapSort(char *vetor[], int M){
        
        build_max_heap(vetor,M);
     
        printf("build_heap:");
        for(int i = 0; i < M; i++){
            printf(" %s",vetor[i]);
        }
        printf("\n");
     
     
        for(int i = M-1; i > 0; i--){
            swap(&vetor[0],&vetor[i]);
            max_heapfy(vetor,i,0);
        }
     
        printf("palavras:");
        for (int i = 0; i < M; i++) {
            printf(" %s", vetor[i]);
        }
        printf("\n");
    }
     
     
    void build_max_heap(char *vetor[], int M){
        for(int i = (M/2) - 1; i >= 0; i--){
            max_heapfy(vetor,M,i);
        }
    }
     
    void max_heapfy(char *vetor[], int tam, int i){
        int l = 2*i + 1;
        int r = 2*i + 2;
     
        int maior = i;
     
        if (l < tam && compara_string(vetor[l], vetor[maior]) > 0) {
        maior = l;
        }
        if (r < tam && compara_string(vetor[r], vetor[maior]) > 0) {
        maior = r;
        }
        if(maior != i){
            swap(&vetor[i], &vetor[maior]);
            max_heapfy(vetor,tam,maior);
        }
    }

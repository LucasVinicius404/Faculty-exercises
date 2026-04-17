#include <stdio.h>
#include <stdlib.h>


void insertionSort(int *vetor, int ini, int n);
int busca_binaria(int *vetor, int elemento, int ini, int fim);


// --- Função Principal ---
int main(){
    int n;
 
    scanf("%d", &n);
 
    int *vetor = malloc(n * sizeof(int));
        if(vetor == NULL){
            return NULL;
        }
 
    for(int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }
    insertionSort(vetor,1,n);
 
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
 
    free(vetor);
    return 0;
}

// --- Implementação do Insertion Sort Recursivo ---
void insertionSort(int *vetor, int ini, int n) {
    if (ini >= n) {
        return;
    }

    int chave = vetor[ini];
    //busca binaria serve para encontrar que posição a chave ou o termo atual vai ser inserido, no vetor ordenado atualmente
    int posicao = busca_binaria(vetor, chave, 0, ini - 1);

    // O nível de recursão é 'n - ini'
    printf("%d %d %d\n", (n - ini), chave, posicao);

    // Desloca os elementos maiores que a chave uma posição para a direita
    for (int j = ini; j > posicao; j--) {
        vetor[j] = vetor[j - 1];
    }

    // Insere a chave na sua posição correta
    vetor[posicao] = chave;

    // Chama a função para o próximo elemento
    insertionSort(vetor, ini + 1, n);
}


// --- Implementação da Busca Binária Iterativa ---
int busca_binaria(int *vetor, int elemento, int ini, int fim) {
    int meio;
    while (ini <= fim) {
        // Usar esta forma para calcular o meio evita overflow com números muito grandes
        meio = ini + (fim - ini) / 2;
        if (elemento < vetor[meio]) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    // Retorna a posição de inserção
    return ini;
}

//void insertionSortIterativo(int *vetor, int n) {
    // O laço principal substitui a recursão.
    // Começa em i = 1, pois o primeiro elemento (índice 0) já forma um "subvetor" ordenado.
    //for (int i = 1; i < n; i++) {
        // --- O corpo do laço é a mesma lógica da função recursiva ---

        // 1. Pega a chave e encontra a posição
        //int chave = vetor[i];
        //int posicao = busca_binaria(vetor, chave, 0, i - 1);

        // 2. Imprime o status (se desejado)
        // O "nível" pode ser calculado da mesma forma
        //printf("%d %d %d\n", (n - i), chave, posicao);

        // 3. Desloca os elementos para a direita
        // A variável 'j' começa de 'i'
        //for (int j = i; j > posicao; j--) {
           // vetor[j] = vetor[j - 1];
       // }

        // 4. Insere a chave na posição correta
        //vetor[posicao] = chave;
   // }
//}
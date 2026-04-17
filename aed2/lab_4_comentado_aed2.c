#include <stdio.h>
#include <stdlib.h>

// Define uma estrutura para representar um ponto cartesiano com coordenadas x e y.
// Usar uma struct garante que as coordenadas x e y de um ponto permaneçam sempre juntas.
typedef struct ponto {
    int x;
    int y;
} ponto;

// --- Protótipos das Funções ---
// Declara as funções antes de serem usadas para que o compilador as reconheça.
void swap(ponto *a, ponto *b);
void quickSort(ponto p[], int ini, int fim, int limiar);
int partition(ponto p[], int ini, int fim);
void insertionSort(ponto p[], int ini, int fim);

// --- Função Principal ---
int main() {
    // limiar: tamanho mínimo do subvetor para usar o Insertion Sort.
    // n: número total de pontos a serem lidos e ordenados.
    int limiar, n;

    // Lê os valores de entrada.
    scanf("%d", &limiar);
    scanf("%d", &n);

    // Aloca dinamicamente memória para um vetor de 'n' pontos.
    ponto *p = malloc(n * sizeof(ponto));
    // Verifica se a alocação de memória foi bem-sucedida.
    if (p == NULL) {
        return 1; // Retorna um código de erro.
    }

    // Lê todas as coordenadas 'x' e as armazena no vetor de structs.
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].x);
    }
    // Lê todas as coordenadas 'y' e as armazena no mesmo vetor.
    for (int j = 0; j < n; j++) {
        scanf("%d", &p[j].y);
    }

    // Chama a função de ordenação principal para o vetor inteiro (de 0 a n-1).
    quickSort(p, 0, n - 1, limiar);

    // Itera sobre o vetor já ordenado para imprimir a saída no formato "(x,y)".
    for (int i = 0; i < n; i++) {
        // Imprime um espaço antes de cada ponto, exceto o primeiro, para a formatação correta.
        if (i > 0) {
            printf(" ");
        }
        printf("(%d,%d)", p[i].x, p[i].y);
    }
    printf("\n"); // Imprime uma nova linha ao final da saída.

    // Libera a memória alocada para o vetor de pontos para evitar vazamentos de memória.
    free(p);
    return 0; // Indica que o programa terminou com sucesso.
}

/**
 * @brief Função auxiliar para trocar a posição de dois pontos na memória.
 * @param a Ponteiro para o primeiro ponto.
 * @param b Ponteiro para o segundo ponto.
 */
void swap(ponto *a, ponto *b) {
    ponto temp = *a; // Guarda o conteúdo do primeiro ponto em uma variável temporária.
    *a = *b;         // Copia o conteúdo do segundo ponto para o primeiro.
    *b = temp;       // Copia o conteúdo original do primeiro ponto (guardado em temp) para o segundo.
}

/**
 * @brief Função principal e recursiva que implementa a lógica de ordenação híbrida.
 * @param p O vetor de pontos.
 * @param ini O índice inicial do subvetor a ser ordenado.
 * @param fim O índice final do subvetor a ser ordenado.
 * @param limiar O tamanho do subproblema abaixo do qual o Insertion Sort é invocado.
 */
void quickSort(ponto p[], int ini, int fim, int limiar) {
    // --- Lógica Híbrida ---
    // Se o número de elementos no subvetor atual for menor que o limiar,
    // usa o Insertion Sort, que é mais eficiente para vetores pequenos, e encerra a chamada.
    if ((fim - ini) + 1 < limiar) {
        insertionSort(p, ini, fim);
        return;
    }

    // --- Lógica Padrão do Quicksort ---
    // A condição (ini < fim) é o caso base da recursão. Se for falso, o subvetor tem 0 ou 1 elemento e já está ordenado.
    if (ini < fim) {
        // Particiona o vetor e obtém o índice do pivô já em sua posição correta.
        int q = partition(p, ini, fim);
        // Chama recursivamente a função para ordenar a sub-lista à esquerda do pivô.
        quickSort(p, ini, q - 1, limiar);
        // Chama recursivamente a função para ordenar a sub-lista à direita do pivô.
        quickSort(p, q + 1, fim, limiar);
    }
}

/**
 * @brief Reorganiza o subvetor com base em um pivô (esquema de partição de Lomuto).
 * Elementos menores ou iguais ao pivô vão para a esquerda, maiores para a direita.
 * @param p O vetor de pontos.
 * @param ini O índice inicial do subvetor.
 * @param fim O índice final do subvetor.
 * @return O índice final do pivô após o particionamento.
 */
int partition(ponto p[], int ini, int fim) {
    // Define o pivô como o valor x do último elemento do subvetor.
    int pivo = p[fim].x;
    // 'i' é um índice que marca a fronteira final da seção de elementos menores que o pivô.
    int i = ini - 1;

    // Percorre o subvetor do início (ini) até o penúltimo elemento (fim-1).
    for (int j = ini; j <= fim - 1; j++) {
        // Se o elemento atual (p[j].x) for menor ou igual ao pivô...
        if (p[j].x <= pivo) {
            i++;             // ...avança a fronteira dos menores...
            swap(&p[i], &p[j]); // ...e troca o elemento atual para dentro dessa fronteira.
        }
    }
    // Ao final, coloca o pivô em sua posição correta, logo após a fronteira dos menores.
    swap(&p[i + 1], &p[fim]);
    // Retorna a posição final do pivô.
    return i + 1;
}

/**
 * @brief Ordena um subvetor usando o algoritmo Insertion Sort.
 * Eficiente para vetores pequenos.
 * @param p O vetor de pontos.
 * @param ini O índice inicial do subvetor.
 * @param fim O índice final do subvetor.
 */
void insertionSort(ponto p[], int ini, int fim) {
    // Itera a partir do segundo elemento do subvetor (ini + 1).
    for (int i = ini + 1; i <= fim; i++) {
        // 'chave' é o ponto que será inserido na parte ordenada do vetor.
        ponto chave = p[i];
        // 'j' começa no elemento anterior à chave.
        int j = i - 1;

        // Move os elementos da parte ordenada (p[ini...i-1]) que são maiores que a chave
        // uma posição para a frente, abrindo espaço para a chave.
        while (j >= ini && p[j].x > chave.x) {
            p[j + 1] = p[j];
            j--;
        }
        // Insere a chave na sua posição correta.
        p[j + 1] = chave;
    }
}
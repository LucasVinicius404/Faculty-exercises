#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Pilha {
    char *chave;
    struct Pilha *prox;
} pilha;

typedef struct no{
    pilha *topo;
    int tam;
}no;

// FUNÇÕES DA PILHA
no *inicializa_pilha(){
    no *p = malloc(sizeof(no));
        if(p == NULL){
            return NULL;
        }
    
    p->topo = NULL;
    p->tam = 0;

    return p;
}

void push(no *p, char *chave) {
    pilha *novo = malloc(sizeof(pilha));
    if (novo == NULL) return;
    novo->chave = strdup(chave);
    novo->prox = p->topo;
    p->topo = novo;
    p->tam++;
}

char *pop(no *p) {
    if (p->topo == NULL) return NULL;
    pilha *remove = p->topo;
    char *valor = remove->chave;
    p->topo = remove->prox;
    free(remove);
    p->tam--;
    return valor;
}

void liberar_pilha(no *p) {
    pilha *aux = p->topo;
    while (aux != NULL) {
        pilha *temp = aux;
        aux = aux->prox;
        free(temp->chave); 
        free(temp);
    }
    free(p);
}

void swap(char **a, char **b) {
    char *aux = *a;
    *a = *b;
    *b = aux;
}

//FUNÇÕES HEAP SORT

void heapfy(char **vet, int i, int tam) {
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int maior = i;

    if (l < tam && strcmp(vet[l], vet[maior]) > 0) {
        maior = l;
    }

    if (r < tam && strcmp(vet[r], vet[maior]) > 0) {
        maior = r;
    }

    if (maior != i) {
        swap(&vet[i], &vet[maior]);
        heapfy(vet, maior, tam);
    }
}

void build_max_heap(char **vet, int tam) {
    for (int i = (tam / 2) - 1; i >= 0; i--) {
        heapfy(vet, i, tam);
    }
}

void heap_sort(char **vet, int tam) {
    build_max_heap(vet, tam);
    for (int i = tam - 1; i > 0; i--) {
        swap(&vet[0], &vet[i]);
        heapfy(vet, 0, i);
    }
}

// FUNÇÕES QUICK_SORT

int partition(char **vet, int ini, int fim) {
    char *pivo = vet[fim];
    int i = ini - 1;

    for (int j = ini; j < fim; j++) {
        // strcmp(a, b) < 0 significa que a vem antes de b no alfabeto
        if (strcmp(vet[j], pivo) < 0) {
            i++;
            swap(&vet[i], &vet[j]);
        }
    }
    swap(&vet[i + 1], &vet[fim]);
    return i + 1;
}

void quick_sort(char **vet, int ini, int fim) {
    if (ini < fim) {
        int q = partition(vet, ini, fim);
        quick_sort(vet, ini, q - 1);
        quick_sort(vet, q + 1, fim);
    }
}

//FUNÇÕES RADIX SORT


void counting_sort(char **vet,int tam,int pos){
    char **b = malloc(tam * sizeof(char *));
    int c[256] = {0};

    for(int i = 0; i < tam;i++){
        c[(unsigned char)vet[i][pos]]++;
    }

    for(int i = 1; i < 256;i++){
        c[i] += c[i - 1];
    }

    for(int i = tam - 1; i >= 0; i--){
        int caractere = (unsigned char)vet[i][pos];
        b[c[caractere] - 1] = vet[i];
        c[caractere]--;
    }

    for(int i = 0; i < tam;i++){
        vet[i] = b[i];
    }

    free(b);
}

void radix_sort(char **vet, int tam, int max_len){
    for(int pos = max_len - 1; pos >= 0; pos--){
        counting_sort(vet,tam,pos);
    }
}


char **inicializa_vet(no *p) {
    if (p->topo == NULL) return NULL;
    int tam = p->tam;
    char **vet = malloc(tam * sizeof(char *)); // Vetor de ponteiros
    pilha *aux = p->topo;
    for (int i = 0; i < tam; i++) {
        vet[i] = aux->chave; 
        aux = aux->prox;
    }
    return vet;
}

void rodar_testes(int tam, char *nome_arquivo) {
    no *p = inicializa_pilha();
    FILE *Arq = fopen(nome_arquivo, "r");
    char buffer[10]; 

    if (Arq == NULL) {
        printf("Erro: Arquivo %s nao encontrado!\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < tam; i++) {
        if (fscanf(Arq, "%s", buffer) == 1) { 
            push(p, buffer);
        }
    }
    fclose(Arq); 

    char **vet_heap = inicializa_vet(p);
    char **vet_quick = inicializa_vet(p);
    char **vet_radix = inicializa_vet(p);

    clock_t t;
    double tempo;

    // Teste Heap Sort
    t = clock();
    heap_sort(vet_heap, tam);
    t = clock() - t;
    tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("Heap_sort (%d): %f s\n", tam, tempo);

    // Teste Quick Sort
    t = clock();
    quick_sort(vet_quick, 0, tam - 1);
    t = clock() - t;
    tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("Quick_sort (%d): %f s\n", tam, tempo);

    // Teste Radix Sort 7 digitos
    t = clock();
    radix_sort(vet_radix, tam,4); 
    t = clock() - t;
    tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("Radix_sort (%d): %f s\n", tam, tempo);


    liberar_pilha(p);
    free(vet_heap);
    free(vet_quick);
    free(vet_radix);
    printf("-------------------------------------------\n");
}

int main(){
    int escolha = -1;

    while(escolha != 0){
        printf("\n--------- MENU TG1 ---------\n");
        printf("1- 10.000 entradas\n2- 50.000 entradas\n3- 100.000 entradas\n4-500.000 entradas\n5-1.000.000 entradas\n0- Finalizar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha){
            case 1:
                rodar_testes(10000,"entrada_10000_str.txt");
                break;
            case 2:
                rodar_testes(50000,"entrada_50000_str.txt");
                break;
            case 3:
                rodar_testes(100000,"entrada_100000_str.txt");
                break;
            case 4:
                rodar_testes(500000,"entrada_500000_str.txt");
                break;
            case 5:
                rodar_testes(1000000,"entrada_1000000_str.txt");
                break;
            case 0:
                printf("finalizando\n");
                break;
            default:
                printf("Opcao invalida!\n");
         }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pilha{
    int chave;
    struct Pilha *prox;
}pilha;

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

void push(no *p,int chave){
    pilha *novo = malloc(sizeof(pilha));
        if(novo == NULL){
            return;
        }
    novo->chave = chave;
    novo->prox = p->topo;
    p->topo = novo;
    p->tam++;
}

int pop(no *p){
    if(p->topo == NULL){
        return -1;
    }

    pilha *remove = p->topo;
    int valor  = p->topo->chave;

    p->topo = remove->prox;
    free(remove);
    p->tam--;
    return valor;
}

void liberar_pilha(no *p){
    pilha *aux = p->topo;
    while(aux != NULL){
        pilha *remove = aux;
        aux = aux->prox;
        free(remove);
    }

    free(p);
}

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

//FUNÇÕES HEAP SORT

void heapfy(int *vet, int i, int tam){
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int maior = i;

    if(l < tam && vet[l] > vet[maior]){
        maior = l;
    }

    if(r < tam && vet[r] > vet[maior]){
        maior = r;
    }

    if(maior != i){
        swap(&vet[i], &vet[maior]);
        heapfy(vet,maior,tam);
    }
}

void build_max_heap(int *vet, int tam){
    for(int i = (tam / 2) - 1; i >= 0; i--){
        heapfy(vet,i,tam);
    }
}

void heap_sort(int *vet, int tam){
    build_max_heap(vet,tam);

    for(int i = tam - 1; i > 0; i--){
        swap(&vet[0],&vet[i]);
        heapfy(vet,0,i);
    }
}

// FUNÇÕES QUICK_SORT

int partition(int *vet, int ini, int fim){
    int pivo = vet[fim];
    int i = ini - 1;

    for(int j = ini; j < fim;j++){
        if(vet[j] < pivo){
            i++;
            swap(&vet[i],&vet[j]);
        }
    }

    swap(&vet[i + 1], &vet[fim]);
    return i + 1;
}

void quick_sort(int *vet, int ini,int fim){
    if(ini < fim){
        int q = partition(vet,ini,fim);
        quick_sort(vet,ini,q - 1);
        quick_sort(vet,q + 1,fim);
    }
}

//FUNÇÕES RADIX SORT


void counting_sort(int *vet,int tam, int exp){
    int *b = malloc(tam * sizeof(int));
    int c[10] = {0};

    for(int i = 0; i < tam; i++){
        c[(vet[i] / exp) % 10]++;
    }

    for(int i = 1; i < 10; i++){
        c[i] += c[i - 1];
    }

    for(int i = tam - 1; i>= 0; i--){
        int digito = (vet[i] / exp) % 10;
        b[c[digito] - 1] = vet[i];
        c[digito]--;
    }

    for(int i = 0; i < tam; i++){
        vet[i] = b[i];
    }

    free(b);
}


void radix_sort(int *vet, int tam) {
    if(tam <= 0){
        return;
    }

    int maior = vet[0];
    for (int i = 1; i < tam; i++) {
        if (vet[i] > maior) maior = vet[i];
    }

    for (int exp = 1; maior / exp > 0; exp *= 10) {
        counting_sort(vet, tam, exp);
    }
}


int *inicializa_vet(no *p){
    if(p->topo == NULL){
        return NULL;
    }

    int tam = p->tam;

    int *vet = malloc(tam * sizeof(int));
    pilha *aux = p->topo;
    for(int i = 0; i < tam;i++){
        vet[i] = aux->chave;
        aux = aux->prox;
    }

    return vet;
}

void rodar_testes(int tam, char *nome_arquivo) {
    no *p = inicializa_pilha();
    FILE *Arq = fopen(nome_arquivo, "r");

    if (Arq == NULL) {
        printf("Erro: Arquivo %s nao encontrado!\n", nome_arquivo);
        return;
    }

    // Carregando a pilha
    for (int i = 0; i < tam; i++) {
        int valor;
        if (fscanf(Arq, "%d", &valor) == 1) {
            push(p, valor);
        }
    }
    fclose(Arq); 

    int *vet_heap = inicializa_vet(p);
    int *vet_quick = inicializa_vet(p);
    int *vet_radix = inicializa_vet(p); 

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
    radix_sort(vet_radix, tam); 
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
                rodar_testes(10000,"entrada_10000_int.txt");
                break;
            case 2:
                rodar_testes(50000,"entrada_50000_int.txt");
                break;
            case 3:
                rodar_testes(100000,"entrada_100000_int.txt");
                break;
            case 4:
                rodar_testes(500000,"entrada_500000_int.txt");
                break;
            case 5:
                rodar_testes(1000000,"entrada_1000000_int.txt");
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
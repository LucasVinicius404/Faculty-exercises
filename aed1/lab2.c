#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

typedef struct cx {
    No **caixa;
    int N;
} Caixa;

No *inicializa();
Caixa *aloca_caixa(int n);
int h(int items, int caixas);
void insere(Caixa *c, int n);
No *retira(Caixa *c, int n);
void imprime(Caixa *c);
void desalocalista(No *p);
void desalocacaixas(Caixa *c);

int main() {
    Caixa *n;
    No *l = NULL;
    No* flag_remove = NULL;
    int num_int, valores, num_caixas, num_remove;

    scanf("%d %d", &num_caixas, &num_int); // para o usuario dizer o numero de caixas e numero de inteiros
    n = aloca_caixa(num_caixas); //chmadas de função para a alocação das caixas
    
    for (int i = 0; i < num_int; i++) {
        scanf("%d", &valores);
        insere(n, valores); // chamada da função para inserir os inteiros nas filas dentros das caixas
    }

    scanf("%d", &num_remove); // digito de remoção do usuario
    flag_remove = retira(n, num_remove); // chamada da função para retirar o digito do usuario
    
    if (flag_remove == NULL) { // se na função for retornado Null era printar-1
        printf("-1\n");
    } else {
        printf("%d\n", flag_remove->info);// caso contrario printa 
        free(flag_remove);//liberação da memoria para flag_remove
    }

    desalocacaixas(n);//chamada de função desalocacaixas que dentro dela a chamada para imprimir e desalocar listas
    return 0; 
}
//função para inicilizar o primeiro termo como nulo
No *inicializa() {
    return NULL;
}
//alocação de memoria na heap para as caixas e para as filas
Caixa *aloca_caixa(int n) {
    Caixa *novacaixa = (Caixa *)malloc(sizeof(Caixa));// alocando espaço para a struct caixa
    if (novacaixa == NULL) {//verificação para ver se foi possivel alocar
        return NULL;
    }

    novacaixa->N = n; //definindo o numero de caixas
    novacaixa->caixa = (No **)malloc(n * sizeof(No *)); //alocando memoria para as listas dentro dessas caixas
    if (novacaixa->caixa == NULL) { //verificação para ver se foi possivel alocar
        free(novacaixa);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        novacaixa->caixa[i] = inicializa(); //iniciando as listas como nulas
    }
    return novacaixa;
}
//função para calculo do indice utilizado para as caixas
int h(int items, int caixas) {
    int calculo = items % caixas;
    return calculo; //retorno do resto dessa instrução
}
//função de inserção do inteiro nas filas
void insere(Caixa *c, int n) {
    int caixa = h(n, c->N); //para receber o indice que ira ser colocado o inteiro
    No *p = (No *)malloc(sizeof(No)); //aloca memoria para um novo nó
    if (p == NULL) { //verificação para ver se foi possivel alocar
        return;
    }
    p->info = n; //armazena o valor do nó
    p->prox = c->caixa[caixa]; // Oproximo aponta para o início da lista existente
    c->caixa[caixa] = p; // Atualiza o início da lista para o novo nó
}
//função para retirar um valor digitado pelo usuario
No *retira(Caixa *c, int n) {
    int caixa = h(n, c->N); //ira calcular em qual caixa estará o digito para remover
    No *ant = NULL;
    No *atual = c->caixa[caixa];

    for (; atual != NULL; ant = atual, atual = atual->prox) {
        if (atual->info == n) { //verifica se o valor é o atual
            if (ant == NULL) {
                c->caixa[caixa] = atual->prox; // se for o o primeiro nó atualiza o novo cabeça de lista
            } else {
                ant->prox = atual->prox; //se não remove o nó do meio da lista
            }
            return atual; //retorna o nó removido
        }
    }
    return NULL; // se passa direto pela função quer dizer que não há o digito logo retorna nulo
}
//função para desalocar a memoria das listas
void desalocalista(No *p) {
    No *atual = p;
    No *temp = NULL;
    for (; atual != NULL; atual = temp) {//loop que percorre a fila até o atual pegar o nulo at
        temp = atual->prox; 
        free(atual);
    }
}
//função para desalocar memoria de caixas 
void desalocacaixas(Caixa *c) {
    imprime(c);//chamada de função de impressão
    for (int i = 0; i < c->N; i++) {
        desalocalista(c->caixa[i]); //chamada da função de desalocar lista para a caixa especifica
    }
    free(c->caixa);//liberação do vetor de listas 
    free(c); //libera a memoria para a estrutura da caixa
}
//função para imprimir
void imprime(Caixa *c) {
    for (int i = 0; i < c->N; i++) {
        No* p = c->caixa[i]; //loop para percorrer as caixas
        for (; p != NULL; p = p->prox) { // loop para imprimir os valores dessa caixa
            printf("%d ", p->info);
        }
        printf("\n");
    }
}


#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int coluna;
    int valor;
    struct no *prox;
}no;

typedef struct matrizEsparsa{
    int n;
    no **linha;
}matriz;

matriz *cria_matriz(int n);
void insere_elementos(matriz *m, int linha, int coluna,int valor);
matriz *soma_matrizes(matriz *A, matriz *b);
matriz *sub_matrizes(matriz *a, matriz*b);
matriz *mult_matriz(matriz *a, matriz *b);
void imprime(matriz *m);
void desaloca_matriz(matriz *m);
void desaloca_lista(no *m);


int main(){
    int controle, n;

    scanf("%d", &controle);
    scanf("%d", &n);

    matriz *ma = cria_matriz(n);
    matriz *mb = cria_matriz(n);
    //inserção dos valores diferentes de zero nas duas listas 
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            int valor;
            scanf("%d", &valor);
            if(valor != 0){
                insere_elementos(ma,i,j,valor);
            }
        }
    }
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            int valor;
            scanf("%d", &valor);
            if(valor != 0){
                insere_elementos(mb,i,j,valor);
            }
        }
    }
    //ponteiro auxilia que recebera o endereço da matriz resultante das operações 
    matriz *resultante = NULL;
    switch(controle){
        case 1:{
            resultante = soma_matrizes(ma,mb);
            break;
        }
        case 2:{
            resultante = sub_matrizes(ma,mb);
            break;
        }
        case 3:{
            resultante = mult_matriz(ma,mb);
            break;
        }
        default:
        desaloca_matriz(ma);
        desaloca_matriz(mb);
        return 0;
    }
    imprime(resultante);
    desaloca_matriz(ma);
    desaloca_matriz(mb);
    desaloca_matriz(resultante);
    return 0; 
}

matriz *cria_matriz(int n){
    //alocação da matriz
    matriz *m = malloc(sizeof(matriz));
        if(m == NULL){
            return NULL;
        }
    //alocação dos vetores que representam as linha nessa matriz
     m->linha = malloc(n * sizeof(no*));
        if(m->linha == NULL){
            free(m);
            return NULL;
        }
    m->n = n;
    //inicio de todos os termos como nulos
for(int i = 0; i < n; i++){
    m->linha[i] = NULL;
}
    return m;
}

void insere_elementos(matriz *m, int linha, int coluna,int valor){
    //alocação de um no 
    no *novo = malloc(sizeof(no));
        if(novo == NULL){
            return;
        }
    //o no ira ser adicionado como primeiro elemento da lista tornando-se o novo cabeça de lista
    novo->coluna = coluna;
    novo->valor = valor;
    novo->prox = m->linha[linha];
    m->linha[linha] = novo;
}

matriz *soma_matrizes(matriz *a, matriz *b){
    matriz *m = cria_matriz(a->n);
    int n = a->n;
   


    for(int i = 0;  i < n; i++){
         //alocação de um vetor de n espaços zerado
        int *aux = calloc(n,sizeof(int)); 
        no *auxA = a->linha[i];
        no *auxB = b->linha[i];
        // loop que percorre as linha da matriz a e adicionas os valores encontrada no vetor em sua posição
        while(auxA != NULL){
            aux[auxA->coluna] += auxA->valor;
            auxA = auxA->prox;
        }
        // loop que percorre as linha da matriz b e adicionas os valores encontrada no vetor em sua posição
        while(auxB != NULL){
            aux[auxB->coluna] += auxB->valor;
            auxB = auxB->prox;
        }
        //loop recursivo para ordenar os elementos no novo vetor
        for(int j = n - 1; j >= 0; j--){
            if(aux[j] != 0){
                insere_elementos(m,i,j,aux[j]);
            }
        }
        free(aux);
    }

    return m;
}

matriz *sub_matrizes(matriz *a, matriz*b){
     matriz *m = cria_matriz(a->n); //inicialização de uma matriz auxiliar que recebera os valores
    int n = a->n;
    
    for(int i = 0;  i < n; i++){
        //alocação de um vetor de n espaços zerado
         int *aux = calloc(n,sizeof(int)); 

        no *auxA = a->linha[i];
        no *auxB = b->linha[i];
        // loop que percorre as linha da matriz a e adicionas os valores encontrada no vetor em sua posição 
        while(auxA != NULL){
            // para matriz a o valor é somado no vetor
            aux[auxA->coluna] += auxA->valor; 
            auxA = auxA->prox;
        }
        // loop que percorre as linha da matriz b e adicionas os valores encontrada no vetor em sua posição
        while(auxB != NULL){ 
            aux[auxB->coluna] -= auxB->valor;
            auxB = auxB->prox;
        }

        for(int j = n - 1; j >= 0; j--){ //loop recursivo para ordenar os elementos no novo vetor
            if(aux[j] != 0){//insere somente valores diferentes de 0
                insere_elementos(m,i,j,aux[j]);
            }
        }
        free(aux);
    }
    
    return m;
}
matriz *mult_matriz(matriz *a, matriz *b) {
    int n = a->n;
    matriz *m = cria_matriz(n);

    for (int i = 0; i < n; i++) {
        // vetor auxiliar para acumular a linha i do produto
        int *aux = calloc(n, sizeof(int));
        
        //auxilar que recebera a cabeca naquele indice
        no *auxA = a->linha[i];
        // percorre cada elemento não-zero em A->linha[i]
        while(auxA != NULL){
            //no auxiliar que recebe indice no elemento não zero de a->linha
            no *auxB = b->linha[auxA->coluna];
            //loop que percorre elementos não zero na linha do indice
            while(auxB != NULL){
                //vetor auxiliar vai receber o valor da multiplicação da linha de a pelas colunas de b
                aux[auxB->coluna] += auxA->valor * auxB->valor;
                auxB = auxB->prox;
            }
            auxA = auxA->prox;
        }
        // insere no resultado só os não-zeros, em ordem decrescente de coluna
        for (int j = n - 1; j >= 0; j--) {
            if (aux[j] != 0) {
                insere_elementos(m, i, j, aux[j]);
            }
        }
        free(aux);
    }
    return m;
}

void imprime(matriz *m){
    for(int i = 0; i < m->n; i++){
        //alocação de um vetor de n espaços zerado
        int *linha = calloc(m->n, sizeof(int));
        no *atual = m->linha[i];
        
        // Preenche com valores não nulos
        while(atual != NULL){
            if(atual->coluna < m->n){
                linha[atual->coluna] = atual->valor;
            }
            atual = atual->prox;
        }
        
        for(int j = 0; j < m->n; j++){
            printf("%d ", linha[j]);
        }
        printf("\n");
        free(linha);
    }
}


void desaloca_matriz(matriz *m){
    //loop que chama o desaloca_lista mandando o primeiro no da lista
    for(int i = 0; i < m->n;i++){
       desaloca_lista(m->linha[i]);
    }
    free(m->linha);
    free(m);
}

void desaloca_lista(no *m){
    no *aux = m;
    while(aux != NULL){
        no *remove = aux;
        aux = aux->prox;
        free(remove);
    }
}




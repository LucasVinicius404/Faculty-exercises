#include <stdio.h>
#include <stdlib.h>
 
typedef struct No {
    int simbolo;
    struct No *ant;
    struct No *prox;
} No;
 
typedef struct Tambor {
    No *cabeca;
} Tambor;
 
typedef struct Maquina {
    int n_tambores;
    Tambor *tambores;
} Maquina;
 
// Declarações de funções
No *inicializa();
Maquina *cria_maquina(int n);
void insere_simbolo(Tambor *c, int valor) ;
void giro(Maquina *l, int *r, int *s, int tam);
void remove_simbolo(Tambor *l, int valor) ;
void desaloca_caixas(Maquina *l);
void desaloca_tambor(Tambor *t);
 
int main() {
    Maquina *c;
    int n, tam,valor;
 
    scanf("%d %d", &n, &tam);
    c = cria_maquina(n);
    //alocações de memorias para enviar como matriz para a função
    int r[n], s[n];
    //recebimento dos valores do tambores
    for (int i = 0; i < n; i++) {
        int v;
        for (int j = 0; j < tam; j++) {
            scanf("%d", &v);
            insere_simbolo((&c->tambores[i]),v);
        }
    }
    //rebimentos do numero de rotações
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    //rebimentos da direção da rotações
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    //rebimentos do numero de remoção
    
    giro(c, r, s, n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        remove_simbolo(&(c->tambores[i]), valor);
    }
 
    giro(c, r, s, n);
    desaloca_caixas(c);
    return 0;
}
//função para inicializar a cabeça como nulo
No *inicializa() {
    return NULL;
}
//função para alocar memoria para a maquina e para os tambores
Maquina *cria_maquina(int n) {
    Maquina *p = malloc(sizeof(Maquina)); //alocação de maquina na heap
    if (p == NULL) {
        return NULL;
    }
    p->n_tambores = n;
    p->tambores = malloc(n * sizeof(Tambor)); //alocação de n espaços de memorias para tambor 
    if (p->tambores == NULL) {
        free(p);
        return NULL;
    }
 
    for (int i = 0; i < p->n_tambores; i++) {
        p->tambores[i].cabeca = inicializa();
    }
 
    return p;
}
//função para inserir numa lista circular os valores digitados pelo usuario no final da lista circular
void insere_simbolo(Tambor *c, int valor) {
            No *novono = malloc(sizeof(No)); //alocação de memoria para os noh
            if (novono == NULL) {
                return;
            }
            novono->simbolo = valor; //o simbolo do novono recebe o valor contido, em v[i][j]
            if (c->cabeca == NULL) { // se tambor não tiver nada logo nulo
                c->cabeca = novono; //ele passa a apontar para o novono
                novono->prox = c->cabeca;
                novono->ant = c->cabeca;
            } else { // caso ele ja aponte para um no
                No* cauda = c->cabeca->ant;
                novono->prox = c->cabeca;
                novono -> ant = cauda;
                cauda->prox = novono;
                c->cabeca->ant = novono;
            }
        }
 
//função para a roleta do caça niquel
void giro(Maquina *l, int *r, int *s, int tam) {
    for(int i = 0; i<l->n_tambores;i++){
        if(s[i]!=0 && s[i]!=1){
            return;
        }
        No *p = l->tambores[i].cabeca;
        int aux = r[i];
        for(int j = 0; j<aux; j++){
            if(s[i]==0){
                p = p->prox;
            }else{
                p = p->ant;
            }
        }
        printf("-%d", p->simbolo);
    }
    printf("-\n");
}
  
//função de remoção
void remove_simbolo(Tambor *l, int valor) {
        No *p = l->cabeca;
        if(p == NULL){
            return;
        } 
        int cont = valor; //cont recebera o valor a ser removido
        do {
            if (p->simbolo == cont) { //se achar o numero
                No *remove = p; //remove recebe o p
                if (p->prox == p) { //se a lista só tiver 1 noh a cabeca recebe nulo
                    l->cabeca = NULL;
                } else {
                    p->ant->prox = p->prox; //o prox de onde o ant de p esta apontando recebe o prox de p
                    p->prox->ant = p->ant;  //o ant de onde o prox de p esta apontando recebe o ant de p
                    if (p == l->cabeca) { //verifica se p é a cabeca
                        l->cabeca = p->prox; //se for cabeca recebe o ant de onde p tá apontando
                    }
                }
                p = p->prox; //para dar seguimento ao loop e não perder referencia de p
                free(remove);
            } else {
                p = p->prox; //se o p não char o simbolo naquele no ele salta pro proximo
            }
        } while (p != l->cabeca);
    }
//funções para desalocação
void desaloca_caixas(Maquina *l) {
    for (int i = 0; i < l->n_tambores; i++) {
        if (l->tambores[i].cabeca != NULL) {
            desaloca_tambor(&(l->tambores[i])); //manda o endereço do tambor[i]
        }
    }
    free(l->tambores); //desaloga os tambores 
    free(l); //desaloca a Maquina
}
 
void desaloca_tambor(Tambor *t) {
    No *p = t->cabeca; //p recebera a cabeca desse tambor
    No *remove;
    if (p == NULL) {
        return;
    }
        do {
            remove = p; //remove recebe p 
            p = p->prox; //p aponta para o noh que o prox dele aponta
            free(remove); //e remove o noh que o remove tinha recebido
        } while (p != t->cabeca); //isso até p for igual a cabeca 
    }
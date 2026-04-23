#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int id;
    int paginas;
    char prioridade;
    struct No *prox;
} No;

typedef struct Fila {
    No *ini;
    No *fim;
} Fila;

Fila *inicializa_lista(void);
void adicionar_tarefa(Fila *f, int id, int page, char prior);
void Processar_tarefa(Fila *f);
void Cancelar_tarefa(Fila *f, int id);
void exibir_tarefa(Fila *f, int exibicao);
void imprimeInverso(No *p);
void desaloca_lista(Fila *f);

int main() {
    Fila *c;
    int num_operacoes, id, paginas, exibicao;
    char operacao[3], prioridade;
    c = inicializa_lista();

    scanf("%d", &num_operacoes);

    if (num_operacoes != 0) {
        for (int i = 0; i < num_operacoes; i++) {
            if (scanf("%s", operacao) != 1) {
                break;
            }
            switch (operacao[0]) {
                case ('A'):
                    scanf("%d %d", &id, &paginas);
                    scanf(" %c", &prioridade);
                    adicionar_tarefa(c, id, paginas, prioridade);
                    break;

                case ('C'):
                    scanf("%d", &id);
                    Cancelar_tarefa(c, id);
                    break;

                case ('E'):
                    scanf("%d", &exibicao);
                    exibir_tarefa(c, exibicao);
                    break;

                case ('P'):
                    Processar_tarefa(c);
                    break;

                default:
                    break;
            }
        }
}
    desaloca_lista(c);
    return 0;
}
//inicializa uma fila no campo de memoria
Fila *inicializa_lista(void) {
    Fila *p = malloc(sizeof(Fila));
    //verificação de alocação
    if (p == NULL) {
        return NULL;
    }
    //inicialização 
    p->ini = NULL;
    p->fim = NULL;
    return p;
}
//adiconar na fila
void adicionar_tarefa(Fila *f, int id, int page, char prior) {
    if(prior != 'U' && prior != 'N'){
        printf("\n");
        return;
    }
    
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        return;
    }

    //recebe os parametros
    novo->id = id;
    novo->paginas = page;
    novo->prioridade = prior;
    novo->prox = NULL;

    if (f->fim == NULL) {//caso a fila esteja vazia
        f->ini = novo;
        f->fim = novo;
    } else {
        No *p = f->ini;

        while(p != NULL){
            if(p->id == id){
                printf("\n");
                free(novo);
                return;
            }
            p = p->prox;
        }

        if (prior == 'U') {
            novo->prox = f->ini;
            f->ini = novo;
        } else if (prior == 'N') {
            f->fim->prox = novo;
            f->fim = novo;
        }
    }
}

void Processar_tarefa(Fila *f){
    if (f->ini == NULL) {
        printf("\n");
        return;
    }

    No *p = f->ini;
    
    printf("%d %d %c\n", p->id, p->paginas, p->prioridade);

    f->ini = p->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free(p);
}

void Cancelar_tarefa(Fila *f, int id) {
    if (f->ini == NULL) {
        printf("\n");
        return;
    }

    No *p = f->ini;
    No *ant = NULL;

    while (p != NULL) {
        if (p->id == id) {
            printf("%d %d %c\n", p->id, p->paginas, p->prioridade);

            if (ant == NULL) {
                f->ini = p->prox;
            } else {
                ant->prox = p->prox;
            }

            if (p == f->fim) {
                f->fim = ant;
            }
            free(p);
            return;
        }

        ant = p;
        p = p->prox;
    }
    printf("\n");
}

void exibir_tarefa(Fila *f, int exibicao){
    if(exibicao != 0 && exibicao != 1){
        printf("\n");
        return;
    }
    No *p = f->ini;

    if (exibicao == 0) {
        if (f->ini == NULL) {
            printf("\n");
        } else {
            for (; p != NULL; p = p->prox) {
                printf("%d %d %c\n", p->id, p->paginas, p->prioridade);
            }
        }
    } else if (exibicao == 1) {
            if (f->ini == NULL) {
                printf("\n");
            } else {
                imprimeInverso(f->ini);
            }
        }
    }


void imprimeInverso(No *p) {
    if(p == NULL){
        return;
    }

    imprimeInverso(p->prox);
    if(p == 0){}
    printf("%d %d %c\n", p->id, p->paginas, p->prioridade);
}

void desaloca_lista(Fila *f){
    No *p = f->ini;
    while(p != NULL){
        No *aux = p;
        p = p->prox;
        free(aux);
        
    }
    free(f);
}

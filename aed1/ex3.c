#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    char frase[51];
    int id;
    struct No *prox;
}no;

typedef struct fila{
    no *inicio;
    no *fim;
}fila;

fila *cria_fila(void);
void insere_fila(fila *f);
void remove_fila(fila *f);
void imprime_fila(fila *f);
void limpa_fila(fila *f);
void libera_fila(fila *f);

int main(){

    fila *f = cria_fila();
    int n = 0;

    do{
        scanf("%d", &n);
    }while(n <= 0 || n > 10);

    getchar();

    char comando[8];

    for(int i = 0; i < n; i++){
        char c;
        int index = 0;
        
        while((c = getchar()) != ' ' && c != '\n' && c != EOF && index < 7){
            comando[index++] = c;
        }
        comando[index] = '\0';

        if(comando[0] == 'E'){
            insere_fila(f);
        }else if(comando[0] == 'D'){
            remove_fila(f);
        }else if(comando[0] == 'C'){
            limpa_fila(f);
        }else if(comando[0] == 'P'){
            imprime_fila(f);
        }
    }

    libera_fila(f);    
}

fila *cria_fila(void){
    fila *f = malloc(sizeof(fila));
    if(f == NULL){
        return NULL;
    }
    
    f->fim = NULL;
    f->inicio = NULL;

    return f;
}

void insere_fila(fila *f){
    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        return;
    }

    scanf("%d", &novo->id);
    getchar();

    int index = 0;
    char c;
    while((c = getchar()) != '\n' && c != EOF && index < 50){
        novo ->frase[index++] = c;
    }
    novo -> frase[index] = '\0';

    if (index == 50 && c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF);
    }

    novo->prox = NULL;
    if(f->fim == NULL){
        f->inicio= novo;
        f->fim = novo;
    }else{
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void remove_fila(fila *f){
    if(f->inicio == NULL){
        printf("Fila vazia!");
        exit(0);
    }
    
    no *p = f->inicio;

    f->inicio = p->prox;

    if(f->inicio == NULL){
        f->fim = NULL;
    }

    free(p);

}

void imprime_fila(fila *f){
    if(f->inicio == NULL){
        printf("\n");
        return;
    }else{
        no *aux = f->inicio;

        for(; aux != NULL; aux = aux->prox){
            printf("ID: %d - ", aux->id);
            int i = 0;
            while(aux->frase[i] != '\0'){
                putchar(aux->frase[i]);
                i++;
            }
            printf("\n");
        }
    }
}

void limpa_fila(fila *f){
    no *aux = f->inicio;

    while(aux != NULL){
        no *remove = aux;
        aux = aux->prox;
        free(remove);
    }
    f->fim = NULL;
    f->inicio = NULL;
}

void libera_fila(fila *f){
    no *aux = f->inicio;

    while(aux != NULL){
        no *remove = aux;
        aux = aux->prox;
        free(remove);
    }
    free(f);
}
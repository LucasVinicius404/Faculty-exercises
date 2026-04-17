#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int id;
    char descricao[50];
    struct No *prox;
    struct No *ant;
}no;

typedef struct lista{
    no *cabeca;
}lista;

lista *cria_lista();
int procura_codigo(lista *l, int id);
void insere_lista(lista *l, int codigo, const char *nome);
void remove_lista(lista *l, int codigo);
void busca_codigo(lista *l, int codigo);
void imprime_lista(lista *l, int selecao);
void imprime_frente(lista *l);
void imprime_reverso(lista *l);
void desaloca_lista(lista *l);

int main() {
    int n;
    char line[128];
    scanf("%d", &n);
    getchar();

    if(n < 1 || n > 100){
        printf("N nao e valido!\n");
        return 0;
    }
    
    lista *l = cria_lista();
    if(l == NULL){
        desaloca_lista(l);
        return 0;
    }

        int linhas = 0;
    // 2) enquanto ainda temos linhas para processar E fgets conseguir ler
    while (linhas < n && fgets(line, sizeof(line), stdin)) {
        linhas++;

        // remove '\n' final sem usar break
        int i = 0;
        while (line[i] != '\0' && line[i] != '\n') {
            i++;
        }
        line[i] = '\0';

        // --- ADD <id> <descricao>
        if (line[0]=='A') {
            int id = 0, pos = 4;
            // parseia o inteiro
            while (line[pos] >= '0' && line[pos] <= '9') {
                id = id * 10 + (line[pos] - '0');
                pos++;
            }
            // pula espaços até a descrição
            while (line[pos] == ' ') pos++;
            // copia descrição (até 49 chars ou até '\0')
            char desc[51] = {0};
            for (int j = 0; j < 50 && line[pos] != '\0'; j++, pos++) {
                desc[j] = line[pos];
            }
            insere_lista(l, id, desc);
        }

        else if (line[0]=='R') {
            int id = 0, pos = 7;
            while (line[pos] >= '0' && line[pos] <= '9') {
                id = id * 10 + (line[pos] - '0');
                pos++;
            }
            remove_lista(l, id);
        }

        else if (line[0]=='P' && line[6]=='F' ) {
            imprime_lista(l, 1);
        }

        else if (line[0]=='P' && line[6]=='R' ) {
            imprime_lista(l, 0);
        }
        else if (line[0]=='S') {
            int id = 0, pos = 7;
            while (line[pos] >= '0' && line[pos] <= '9') {
                id = id * 10 + (line[pos] - '0');
                pos++;
            }
            busca_codigo(l, id);
        }
    }

    if (linhas < n) {
        printf("N superior ao numero de comandos!\n");
    }


    desaloca_lista(l);
    return 0;
}

lista *cria_lista(){
    lista *l = malloc(sizeof(lista));
        if(l == NULL){
            return NULL;
        }
    
    l->cabeca = NULL;
    return l;
}

int procura_codigo(lista *l, int id){
  if(l->cabeca != NULL){
      no *p = l->cabeca;
        do{
            if(p->id != id){
                p = p->prox;
            }else{
              return 0;
            }
        }while(p != l->cabeca);
    }
  return 1;
}

void insere_lista(lista *l, int codigo, const char *nome){
    if(!procura_codigo(l,codigo)){
        printf("Codigo ja existente!\n");
        return;
    }

    no *novo = malloc(sizeof(no));
        if(novo == NULL){
            return;
        }
        int i = 0;
        for(; i <51; i++){
            novo->descricao[i] = nome[i];
        }
        novo->descricao[i] = '\0';
        novo->id = codigo;
    if(l->cabeca == NULL){
        l->cabeca = novo;
        novo->ant = novo;
        novo -> prox = novo;
        }else{
        no *aux = l->cabeca;
        novo->prox = l->cabeca;
        novo->ant = aux->ant;
        aux->ant->prox = novo;
        l->cabeca->ant = novo;
    }
}

void remove_lista(lista *l, int codigo){
    if(l->cabeca == NULL){
        printf("Codigo nao encontrado!\n");
        return;
    }else{
        no *p = l->cabeca;

        do{
            if(p->id == codigo){
                if(p->prox == p){
                    free(p);
                    l->cabeca = NULL;
                    return;
                }else{
                    p->ant->prox = p->prox;
                    p->prox->ant = p->ant;
                    if(p == l->cabeca){
                        l->cabeca = p->prox;
                    }
                    free(p);
                    return;
                }
            }
        p = p->prox;
        }while(p != l->cabeca);
        printf("Codigo nao encontrado!\n");
    }
}

void busca_codigo(lista *l, int codigo){
    if(l->cabeca == NULL){
        printf("Codigo nao encontrado!\n");
        return;
    }else{
        no *p = l->cabeca;
        do{
            if(p->id == codigo){
                printf("Codigo: %d - %s\n",p->id,p->descricao);
                return;
            }
        p = p->prox;
        }while( p != l->cabeca);

        printf("Codigo nao encontrado!\n");
    }
}

void imprime_lista(lista *l, int selecao){
    if(l->cabeca != NULL){
        if(selecao == 1){
            imprime_frente(l);
        }else if(selecao == 0){
            imprime_reverso(l);
        }
    }else{
        printf("Lista vazia!\n");
    }
}

void imprime_frente(lista *l){
    no *p = l->cabeca;
      do{
        printf("Codigo: %d - %s\n",p->id,p->descricao);
        p = p->prox;
      }while(p != l ->cabeca);  
}

void imprime_reverso(lista *l) {
    no *p = l->cabeca->ant;
    no *inicio = p;
    do {
        printf("Codigo: %d - %s\n", p->id, p->descricao);
        p = p->ant;
    } while (p != inicio);
}

void desaloca_lista(lista *l){
    if(l->cabeca == NULL){
        free(l);
        return;
    }
        no *p = l->cabeca;
            do{
                no *aux = p;
                p = p->prox;
                free(aux);
            }while(p != l->cabeca);
    free(l);
}

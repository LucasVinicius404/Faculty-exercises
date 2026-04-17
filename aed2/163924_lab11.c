    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct no{
        int chave;
        struct no *prox;
    }no;
     
    typedef struct lista{
        no *ini;
        no *fim;
    }lista;
     
    typedef struct hash{
        int tam;
        struct lista *vetor;
    }hash;
     
    hash *inicializa_hash(int tam);
    int funcao_hash(int chave, int tam);
    void insere_hash(hash *h, int chave);
    void busca_e_remove(hash *h, int chave);
    void imprime_hash(hash *h, int linha);
    void remove_hash(hash *h);
     
    int main(){
        int tam_hash;
     
        scanf("%d", &tam_hash);
     
        hash *h = inicializa_hash(tam_hash);
     
        int elemento = 0;
        while(elemento != -1 ){
            scanf("%d", &elemento);
            if(elemento != -1){
                insere_hash(h,elemento);
            }
        }
     
        int busca,linha;
        scanf("%d", &busca);
        busca_e_remove(h,busca);
        scanf("%d",&linha);
        imprime_hash(h,linha);
     
        remove_hash(h);
        return 0;
     
    }
     
     
    hash *inicializa_hash(int tam){
        hash *h = malloc(sizeof(hash));
            if(h == NULL){
                return NULL;
            }
        
        h->tam = tam;
        h->vetor = malloc(tam * sizeof(lista));
            if(h->vetor == NULL){
                free(h);
                return NULL;
            }
     
        for(int i = 0; i < tam;i++){
            h->vetor[i].ini = h->vetor[i].fim = NULL;
        }
     
        return h;
    }
     
    int funcao_hash(int chave, int tam){
        return chave % tam;
    }
     
    void insere_hash(hash *h, int chave){
        int idx = funcao_hash(chave,h->tam);
        no *novo = malloc(sizeof(no));
            if(novo == NULL){
                return;
            }
     
        novo->chave = chave;
        novo->prox = NULL;
     
        if(h->vetor[idx].fim == NULL){
            h->vetor[idx].ini = h->vetor[idx].fim = novo;
        }else{
            h->vetor[idx].fim->prox = novo;
            h->vetor[idx].fim = novo;
        }
    }
     
    void busca_e_remove(hash *h, int chave){
        int idx = funcao_hash(chave,h->tam);
     
        if(h->vetor[idx].ini == NULL){
            printf("Valor nao encontrado\n");
            return;
        }
     
        no *ant = NULL;
        no *aux = h->vetor[idx].ini;
     
        while(aux != NULL && aux->chave != chave){
            ant = aux;
            aux = aux->prox;
        }
     
        if(aux == NULL){
            printf("Valor nao encontrado\n");
            return;
        }
     
        if(ant == NULL){
            h->vetor[idx].ini = aux->prox;
        }else{
            ant->prox = aux->prox;
        }
     
        if(aux == h->vetor[idx].fim){
            h->vetor[idx].fim = ant;
        }
     
        free(aux);
     
    }
     
    void imprime_hash(hash *h, int linha){
        printf("[%d]",linha);
        if(h->vetor[linha].ini == NULL){
            return;
        }
     
        no *aux = h->vetor[linha].ini;
        
        while(aux != NULL){
            printf(" %d",aux->chave);
            aux = aux->prox;
        }
    }
     
    void remove_hash(hash *h){
        for(int i = 0; i < h->tam;i++){
            no *aux = h->vetor[i].ini;
                while(aux != NULL){
                    no *remove = aux;
                    aux = aux->prox;
                    free(remove);
                }
        }
        free(h->vetor);
        free(h);
    }
    #include <stdio.h>
    #include <stdlib.h>
    
    typedef struct no{
        struct no *prox;
        int valor;
    }no;

    typedef struct lista{
        no *cabeca;
    }lista;

    lista *inicializa_lista();
    void insere_lista(lista *l,int valor);
    void imprime_lista(lista *l);
    void free_lista(lista *l);
    no *mergeSort(no *cabeca);
    no *merge(no *a, no *b);
     
    int main(){
        int n,valor;
        lista *l = inicializa_lista();
        
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%d", &valor);
            insere_lista(l,valor);
        }
        l->cabeca = mergeSort(l->cabeca);

        imprime_lista(l);
        free_lista(l);
        return 0;
    }

    lista *inicializa_lista(){
        lista *l = malloc(sizeof(lista));
            if(l == NULL){
                return NULL;
            }
        l->cabeca = NULL;
        return l;
    }

    void insere_lista(lista *l, int valor){
        no *novo = malloc(sizeof(no));
            if(novo == NULL){
                return;
            }
        novo -> valor = valor;
        novo ->prox = NULL;
        if(l->cabeca == NULL){
            l->cabeca = novo;
        }else{
            no *aux = l->cabeca;

            while(aux->prox != NULL){
                aux = aux ->prox;
            }
            aux ->prox = novo;
        }
    }

    void imprime_lista(lista *l){
        if(l->cabeca == NULL){
            return;
        }

        no *aux = l->cabeca;

        while(aux != NULL){
            printf("%d ",aux->valor);
            aux = aux->prox;
        }
    }

     void free_lista(lista *l){
        if(l->cabeca == NULL){
            return;
        }
        
        no *aux = l->cabeca;

        while(aux != NULL){
            no *remove = aux;
            aux = aux->prox;
            free(remove);
        }
        free(l);
    }

    no *mergeSort(no *cabeca){
        if(cabeca == NULL || cabeca->prox == NULL){
            return cabeca;
        }
        //cria dois vetores para percorrer a lista
        no *slow = cabeca;
        no *fast = cabeca->prox;
        while(fast != NULL && fast->prox != NULL){
            //o left percorre mais devagar pois ele vai ser a nossa marcação do meio
            slow = slow->prox;
            fast = fast->prox->prox;
        }
        //a cabeca do lado direito será o proximo do meio
        no *right_side = slow->prox;
        //transforma a lista em duas independentes
        slow->prox = NULL;

        //chamada para ordenação da primeira metade
        no *primeira_metade = mergeSort(cabeca);
        //cahmada para ordenação da segunda metade
        no *segunda_metade = mergeSort(right_side);

        return(merge(primeira_metade,segunda_metade));
    }
    
    no *merge(no *a, no *b){
        //casos base
        if(a == NULL){
            return b;
        }else if(b == NULL){
            return a;
        }

        no *resultado;
        if(a->valor <= b->valor){
            resultado = a;
            resultado->prox = merge(a->prox,b);
        }else{
            resultado = b;
            resultado->prox = merge(a,b->prox);
        }
        return resultado;
    }
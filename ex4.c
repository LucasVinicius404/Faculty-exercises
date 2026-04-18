    #include <stdio.h>
    #include <stdlib.h>
 
    typedef struct No {
        int valor;
        struct No *prox;
    } no;
 
    typedef struct Pilha {
        char nome[50];
        no *topo;
        struct Pilha *next;
    } pilha;
    
    pilha *init_pilha(pilha *cabeca, const char *nome);
    int nome_iguais(pilha *cabeca, const char *nome);
    void Push(pilha *cabeca, const char *nome, int valor);
    void Pop(pilha **cabeca, const char *nome);
    void Top_pilha(pilha *cabeca, const char *nome);
    void Print_pilha(pilha *cabeca, const char *nome);
    void Show_lista(pilha *cabeca);
    void merge_pilha(pilha **cabeca);
    void split_pilha(pilha **cabeca);
    void libera_pilha(pilha *cabeca);
    void remove_pilha(pilha **cabeca, pilha *alvo);

    int main(){
     pilha *cabeca = NULL;
    int n = 0;
 
    while (n < 1 || n > 100) {
        scanf("%d", &n);
    }
    getchar();
 
    for (int i = 0; i < n; i++) {
        char nome_p[50];
        char c;
        int cont = 0;
        while ((c = getchar()) != ':' && c != '\n' && c != EOF && c!= ' ' && cont < 49) {
            nome_p[cont++] = c;
        }
        nome_p[cont] = '\0';
 
        int flag = 0;
 
        if(c == ':'){
            flag = 1;
        }
 
        if(flag){
        char comando[8];
        int index = 0;
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && index < 7) {
            comando[index++] = c;
        }
        comando[index] = '\0';
 
        if (comando[0] == 'I') {
            cabeca = init_pilha(cabeca, nome_p);
        } else if (comando[0] == 'P' && comando[1] == 'U') {
            int valor;
            scanf("%d", &valor);
            getchar();
            Push(cabeca, nome_p, valor);
        } else if (comando[0] == 'P' && comando[1] == 'O') {
            Pop(&cabeca, nome_p);
        } else if (comando[0] == 'T') {
            Top_pilha(cabeca, nome_p);
        } else if (comando[0] == 'P' && comando[1] == 'R') {
            Print_pilha(cabeca, nome_p);
        }
        }else{
        
         if (nome_p[0] == 'M') {
            merge_pilha(&cabeca);
        } else if (nome_p[0] == 'S' && nome_p[1] == 'P') {
            split_pilha(&cabeca);
        } else if (nome_p[0] == 'S' && nome_p[1] == 'H') {
            Show_lista(cabeca);
            }
     }
 }
    libera_pilha(cabeca);
    return 0;
}
 
    pilha *init_pilha(pilha *cabeca, const char *nome) {
        pilha *aux = cabeca;
         while (aux != NULL) {
        if (nome_iguais(aux, nome)) {
            return cabeca; // Pilha já existe, retorna sem criar
        }
        aux = aux->next;
    }
        pilha *p = malloc(sizeof(pilha));
        if (p == NULL) {
            return NULL;
        }
        int i = 0;
        while (nome[i] != '\0') {
            p->nome[i] = nome[i];
            i++;
        }
        p->nome[i] = '\0';
        p->topo = NULL;
        p->next = cabeca;
        return p;
    }
 
    int nome_iguais(pilha *cabeca, const char *nome){
        int i = 0;
        while((nome[i] != '\0' || cabeca->nome[i] != '\0') && i <50){
            if(cabeca->nome[i] != nome[i]){
                return 0;
            }
            i++;
        }
        return (cabeca->nome[i] == '\0' && nome[i] == '\0');
    }
 
    void Push(pilha *cabeca, const char *nome, int valor) {
        pilha *aux = cabeca;
 
        while (aux != NULL) {
            if (nome_iguais(aux,nome)) {
                no *novo = malloc(sizeof(no));
                if (novo == NULL) {
                    exit(0);
                }
                novo->valor = valor;
                novo->prox = aux->topo;
                aux->topo = novo;
                return;
            }
 
            aux = aux->next;
        }
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
 
    void Pop(pilha **cabeca, const char *nome) {
        pilha *aux = *cabeca;
 
        while (aux != NULL) {
            if (nome_iguais(aux,nome)) {
                if (aux->topo == NULL) {
                    printf("Pilha %s vazia!\n",nome);
                    exit(0);
                } else {
                    no *remove = aux->topo;
                    aux->topo = remove->prox;
                    free(remove);
 
                    if(aux->topo == NULL){
                        remove_pilha(cabeca,aux);
                        return;
                    }
                }
            }
            aux = aux->next;
        }
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
 
    void Top_pilha(pilha *cabeca, const char *nome) {
        
        pilha *aux = cabeca;
 
        while (aux != NULL) {
            if (nome_iguais(aux,nome)) {
                if (aux->topo == NULL) {
                    printf("Pilha %s vazia!\n",nome);
                    exit(0);
                } else {
                    printf("%d\n", aux->topo->valor);
                    return;
                }
            }
            aux = aux->next;
        }
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
 
    void Print_pilha(pilha *cabeca, const char *nome) {
        pilha *aux = cabeca;
 
        while (aux != NULL) {
            if (nome_iguais(aux,nome)) {
                if (aux->topo == NULL) {
                    printf("[]\n");
                    return;
                } else {
                    no *imprime = aux->topo;
                    printf("[");
                    while (imprime != NULL) {
                        printf("%d", imprime->valor);
                        if (imprime->prox != NULL) {
                            printf(", ");
                        }
                        imprime = imprime->prox;
                    }
                    printf("]\n");
                    return;
                }
            }
            aux = aux->next;
        }
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
 
void Show_lista(pilha *cabeca) {
    if (cabeca == NULL) {
        printf("\n");
        return;
    }

    pilha *aux = cabeca;

    while (aux != NULL) {
        printf("%s: [", aux->nome);
        no *imprime = aux->topo;

        while (imprime != NULL) {
            printf("%d", imprime->valor);
            if (imprime->prox != NULL) {
                printf(", ");
            }
            imprime = imprime->prox;
        }

        printf("]\n");
        aux = aux->next;
    }
}
    
 
   void merge_pilha(pilha **cabeca){
    char nome1[50], nome2[50];
    char c;
        int cont = 0;
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && cont < 49) {
            nome1[cont++] = c;
        }
        nome1[cont] = '\0';
        
        int index = 0;
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && index < 49) {
            nome2[index++] = c;
        }
        nome2[index] = '\0';
    
    pilha *ant = NULL;
    pilha *a = NULL, *b = NULL, *prevB = NULL;
    for(pilha *aux = *cabeca ; aux != NULL; ant =aux, aux = aux->next){
        if(nome_iguais(aux,nome1)){
            a = aux;
        }
        if(nome_iguais(aux,nome2))  {
            b = aux;
            prevB = ant;
        }
    }
 
    if(a != NULL && b != NULL){
        if(b->topo != NULL){
            no *p = b->topo;
            while(p->prox != NULL){
                p = p->prox;
            }
            p->prox = a->topo;
            a->topo = b->topo;
        }
 
        if(prevB != NULL){
            prevB -> next = b->next;
        }else{
            *cabeca = b->next;
        }
        free(b);
 
    }else{
        printf("Erro: pilhas nao encontradas!\n");
        exit(0);
    }
}
 
    void split_pilha(pilha **cabeca) {
        char nome[50], novoNome[50];
    char c;
        int cont = 0;
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && cont < 49) {
            nome[cont++] = c;
        }
        nome[cont] = '\0';
        
        int index = 0;
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && index < 49) {
            novoNome[index++] = c;
        }
        novoNome[index] = '\0';
 
        int quant;
        scanf("%d", &quant);
        getchar();
    
        pilha *aux = *cabeca;
        while (aux != NULL && !nome_iguais(aux, nome)) {
            aux = aux->next;
        }
 
        if (aux == NULL) {
            printf("Pilha %s nao encontrada!\n", nome);
            exit(0);
        }
 
        pilha *nova = init_pilha(*cabeca, novoNome);
        *cabeca = nova;
 
        no *temp = NULL;
        int i = 0;
        while (i < quant && aux->topo != NULL) {
            no *retira = aux->topo;
            aux->topo = retira->prox;
 
            retira->prox = temp;
            temp = retira;
            i++;
        }
 
        while (temp != NULL) {
            no *retira = temp;
            temp = temp->prox;
 
            retira->prox = nova->topo;
            nova->topo = retira;
        }
        if(aux->topo == NULL){
            remove_pilha(cabeca,aux);
        }
    }
 
    void libera_pilha(pilha *cabeca) {
        pilha *atual = cabeca;
        while(atual != NULL) {
            pilha *prox_pilha = atual->next;
            // Liberar nós da pilha
            no *no_atual = atual->topo;
            while(no_atual != NULL) {
                no *temp = no_atual;
                no_atual = no_atual->prox;
                free(temp);
            }   
            free(atual);
            atual = prox_pilha;
        }
    }
 
void remove_pilha(pilha **cabeca, pilha *alvo) {
    if (*cabeca == NULL || alvo == NULL) return;

    pilha *anterior = NULL;
    pilha *atual = *cabeca;

    // Encontrar a pilha anterior à alvo
    while (atual != NULL && atual != alvo) {
        anterior = atual;
        atual = atual->next;
    }

    // Se a pilha não for encontrada
    if (atual == NULL) return;

    // Ajustar ponteiros
    if (anterior == NULL) {
        // O alvo é a cabeça da lista
        *cabeca = atual->next;
         free(atual);
    } else {
        anterior->next = atual->next;
    }
}

 

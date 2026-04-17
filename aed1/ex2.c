#include <stdio.h>
#include <stdlib.h>


typedef struct machine {
    int valor;
    struct machine *prox;
} machine;

typedef struct Pilha {
    machine *topo;
} pilha;

pilha* cria_pilha(void);
void Push(pilha *p, int valor);
void Pop(pilha *p);
void Clear_pilha(pilha *p);
void Print(pilha *p);
int verifica(pilha* p);
void operacoes(pilha *p, char op);
void Dup_pilha(pilha *p);
void Swap_pilha(pilha *p);
void Roll_pilha(pilha *p,int roll);
void Libera_pilha(pilha *p);

int main() {
    pilha *principal = cria_pilha();
    int N = 0, valor = 0, roll = 0, printou = 0;

    while (N < 1 || N > 100) {
        scanf("%d", &N);
    }
    getchar();

    char comando[10];

    for (int i = 0; i < N; i++) {
        int index = 0;
        char c;
        //o while recebera os caracteres e amarzenara no vetor até encontra uma condição de para que pode ser espaço, quebra de linha ou fim do arquivo
        while ((c = getchar()) != ' ' && c != '\n' && c != EOF && index < 9) {
            comando[index++] = c;
        }
        comando[index] = '\0';

        if (comando[0] == 'P' && comando[1] == 'U') {
            scanf("%d", &valor);
            getchar();
            Push(principal, valor);
        }
        else if (comando[0] == 'P' && comando[1] == 'O') {
            Pop(principal);
        }
        else if (comando[0] == 'A') {
            operacoes(principal, 'a');
        }
        else if (comando[0] == 'S' && comando[1] == 'U') {
            operacoes(principal, 's');
        }
        else if (comando[0] == 'M') {
            operacoes(principal, 'm');
        }
        else if (comando[0] == 'D' && comando[1] == 'I') {
            operacoes(principal, 'd');
        }
        else if (comando[0] == 'D' && comando[1] == 'U') {
            Dup_pilha(principal);
        }
        else if (comando[0] == 'S' && comando[1] == 'W') {
            Swap_pilha(principal);
        }
        else if (comando[0] == 'R' && comando[1] == 'O') {
            scanf("%d", &roll);
            getchar();
            Roll_pilha(principal,roll);
        }
        else if (comando[0] == 'C' && comando[1] == 'L') {
            Clear_pilha(principal);
        }
        else if (comando[0] == 'P') {
            Print(principal);
            printou = 1;
            printf("\n");
        }
    }
    if(printou == 0){
        Print(principal);
    }

    Libera_pilha(principal);
    return 0;
}

pilha* cria_pilha(void) {
    pilha *n = malloc(sizeof(pilha));
    if (n == NULL) {
        return NULL;
    }
    n->topo = NULL;
    return n;
}

void Push(pilha *p, int valor) {
    machine *novo = malloc(sizeof(machine));
    if (novo == NULL) {
        return;
    }
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

void Pop(pilha *p) {
    if (p->topo == NULL) {
        printf("Erro: Pilha vazia!");
        exit(0);
    } else {
        machine *c = p->topo;
        p->topo = c->prox;
        free(c);
    }
}

void Clear_pilha(pilha *p) {
    if (p->topo == NULL) {
        return;
    }
    Pop(p);
    Clear_pilha(p);
}

void Print(pilha *p) {
        machine *c = p->topo;
        for (; c != NULL; c = c->prox) {
            printf("%d ", c->valor);
        }
    }

int verifica(pilha* p) {
    int cont = 0;
    machine *no = p->topo;
    for (; no != NULL; no = no->prox) {
        cont++;
    }
    return cont;
}

void operacoes(pilha *p, char op) {
    int verify = verifica(p);
    if (verify < 2) {
        printf("Erro: Elementos insuficiente para operacao!");
        exit(0);
    } else {
        int resultado = 0;
        int ult = p->topo->valor;
        Pop(p);
        int pen = p->topo->valor;
        Pop(p);

        switch (op) {
            case 'a':
                resultado = pen + ult;
                break;
            case 's':
                resultado = pen - ult;
                break;
            case 'd':
                if (ult == 0) {
                    printf("Erro: Divisao por zero!");
                    exit(0);
                }
                resultado = pen / ult;
                break;
            case 'm':
                resultado = pen * ult;
                break;
        }
        Push(p, resultado);
    }
}

void Dup_pilha(pilha *p) {
    if (p->topo == NULL) {
        printf("Erro: Pilha vazia para DUP!");
        exit(0);
    } else {
        Push(p, p->topo->valor);
    }
}

void Swap_pilha(pilha *p) {
    int verify = verifica(p);
    if (verify < 2) {
        printf("Erro: Pilha insuficiente para SWAP!");
        exit(0);
    } else {
        int topo = p->topo->valor;
        Pop(p);
        int prox = p->topo->valor;
        Pop(p);
        Push(p, topo);
        Push(p, prox);
    }
}

void Roll_pilha(pilha *p,int roll) {
    int verify = verifica(p);
    if (roll < 1 || roll > verify) {
        printf("Erro: Posicao invalida!");
        exit(0);
    } else {
        pilha *aux = malloc(sizeof(pilha));
        aux->topo = NULL;
        for (int i = 0; i < roll - 1; i++) {
            Push(aux, p->topo->valor);
            Pop(p);
        }
        int valor = p->topo->valor;
        Pop(p);
        for (int i = 0; i < roll - 1; i++) {
            Push(p, aux->topo->valor);
            Pop(aux);
        }
        Push(p, valor);
        Libera_pilha(aux);
    }
}

void Libera_pilha(pilha *p) {
    machine *c = p->topo;
    while (c != NULL) {
        machine *aux = c;
        c = c->prox;
        free(aux);
    }
    free(p);
}
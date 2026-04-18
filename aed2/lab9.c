#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no *prox;
    int id;
} no;

typedef struct grafo {
    struct no **adj;
    int vertices;
} grafo;

typedef struct fila {
    int *v;
    int cabeca;
    int final;
    int capacidade;
} fila;

grafo *inicializa_grafo(int vertices);
void adiciona_grafo(grafo *g, int v1, int v2);
void desaloca_grafo(grafo *g);
fila *inicializa_fila(int tam);
void insere_fila(fila *f, int vertice);
int remove_fila(fila *f);
void desaloca_fila(fila *f);
void bfs(grafo *g, int s, int *cor, int *dist, int *pred);
void imprime_caminho(int s, int v, int *pred);

int main() {
    int vertices, arestas;

    scanf("%d %d", &vertices, &arestas);

    grafo *g = inicializa_grafo(vertices);

    for (int i = 0; i < arestas; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        adiciona_grafo(g, v1, v2);
    }

    int *cor = calloc(vertices, sizeof(int));
    int *distancia = malloc(vertices * sizeof(int));
    int *predecessor = malloc(vertices * sizeof(int));

    bfs(g, 0, cor, distancia, predecessor);

    for (int i = 0; i < vertices; i++) {
        if (distancia[i] == -1) {
            printf("Nao existe caminho de 0 a %d", i);
        } else {
            imprime_caminho(0, i, predecessor);
        }
        printf("\n");
    }

    desaloca_grafo(g);
    free(cor);
    free(distancia);
    free(predecessor);
    return 0;
}

grafo *inicializa_grafo(int vertices) {
    grafo *g = malloc(sizeof(grafo));
    if (g == NULL) {
        return NULL;
    }
    g->vertices = vertices;
    g->adj = malloc(vertices * sizeof(no *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void adiciona_grafo(grafo *g, int v1, int v2) {
    no *novo = malloc(sizeof(no));
    if (novo == NULL) return;
    novo->id = v2;
    novo->prox = NULL;

    if (g->adj[v1] == NULL) {
        g->adj[v1] = novo;
    } else {
        no *p = g->adj[v1];
        while (p->prox != NULL) p = p->prox;
        p->prox = novo;
    }

    no *novo1 = malloc(sizeof(no));
    if (novo1 == NULL) return;
    novo1->id = v1;
    novo1->prox = NULL;

    if (g->adj[v2] == NULL) {
        g->adj[v2] = novo1;
    } else {
        no *q = g->adj[v2];
        while (q->prox != NULL) q = q->prox;
        q->prox = novo1;
    }
}

void desaloca_grafo(grafo *g) {
    for (int i = 0; i < g->vertices; i++) {
        no *remove = g->adj[i];
        while (remove != NULL) {
            no *aux = remove;
            remove = remove->prox;
            free(aux);
        }
    }
    free(g->adj);
    free(g);
}

fila *inicializa_fila(int tam) {
    fila *f = malloc(sizeof(fila));
    if (f == NULL) {
        return NULL;
    }
    f->cabeca = f->final = 0;
    f->capacidade = tam + 1;
    f->v = malloc(f->capacidade * sizeof(int));
    if (f->v == NULL) {
        free(f);
        return NULL;
    }
    return f;
}

void insere_fila(fila *f, int vertice) {
    if ((f->final + 1) % f->capacidade == f->cabeca) {
        return;
    }
    f->v[f->final] = vertice;
    f->final = (f->final + 1) % f->capacidade;
}

int remove_fila(fila *f) {
    if (f->cabeca == f->final) {
        return -1;
    }
    int u = f->v[f->cabeca];
    f->cabeca = (f->cabeca + 1) % f->capacidade;
    return u;
}

void desaloca_fila(fila *f) {
    free(f->v);
    free(f);
}

void bfs(grafo *g, int s, int *cor, int *dist, int *pred) {
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }
    cor[s] = 1;
    dist[s] = 0;

    fila *f = inicializa_fila(g->vertices);
    insere_fila(f, s);

    while (f->cabeca != f->final) {
        int u = remove_fila(f);
        no *vizinhos = g->adj[u];
        while (vizinhos != NULL) {
            int v = vizinhos->id;
            if (cor[v] == 0) {
                cor[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                insere_fila(f, v);
            }
            vizinhos = vizinhos->prox;
        }
        cor[u] = 2;
    }
    desaloca_fila(f);
}

void imprime_caminho(int s, int v, int *pred) {
    if (v == s) {
        printf("-%d-", s);
        return;
    }
    if (pred[v] == -1) {
        return;
    }
    imprime_caminho(s, pred[v], pred);
    printf("%d-", v);
}

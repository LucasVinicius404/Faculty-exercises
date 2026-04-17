    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
     
    typedef struct no {
        struct no *prox;
        int peso;
        int id;
    } no;
     
    typedef struct grafo {
        struct no **adj;
        int vertices;
    } grafo;
     
    typedef struct Elemento {
        int id;
        int chave;
    } Elemento;
     
    typedef struct fila {
        Elemento *array;
        int *mapa;
        int capacidade;
        int tam_heap;
    } fila;
     
    grafo *inicializa_grafo(int vertices);
    void insere_grafo(grafo *g, int u, int v, int peso);
    void desaloca_grafo(grafo *g);
    fila *inicializa_fila(int tam);
    void swap(fila *f, int i, int j);
    void min_heap_insert(fila *f, int id, int chave);
    void min_heapify(fila *f, int i);
    Elemento min_heap_extract(fila *f);
    void min_heap_decrease(fila *f, int id, int nova_chave);
    void desaloca_fila(fila *f);
    int parent(int i);
    int left(int i);
    int right(int i);
    void inicializa_single_source(grafo *g, int fonte, int *dist, int *pred);
    int relax(int v1, int v2, int peso, int *dist, int *pred);
    int bellman_ford(grafo *g, int s, int *dist, int *pred);
    void dijkstra(grafo *g, int fonte, int *dist, int *pred);
     
     
    int main() {
        int arestas, vertices;
        scanf("%d %d", &vertices, &arestas);
     
        grafo *g = inicializa_grafo(vertices);
     
        for (int i = 0; i < arestas; i++) {
            int u, v, peso;
            scanf("%d %d %d", &u, &v, &peso);
            insere_grafo(g, u, v, peso);
        }
     
        int v_fonte;
        scanf("%d", &v_fonte);
     
        int *dist = malloc(vertices * sizeof(int));
        if (dist == NULL) {
            desaloca_grafo(g);
            return 0;
        }
        
        int *pred = malloc(vertices * sizeof(int));
        if (pred == NULL) {
            desaloca_grafo(g);
            free(dist);
            return 0;
        }
     
        if (bellman_ford(g, v_fonte, dist, pred) == 0) {
            printf("Ha um ciclo negativo\n");
        } else {
            dijkstra(g, v_fonte, dist, pred);
        }
     
        free(dist);
        free(pred);
        desaloca_grafo(g);
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
     
    void insere_grafo(grafo *g, int u, int v, int peso) {
        no *novo = malloc(sizeof(no));
        if (novo == NULL) {
            return;
        }
        novo->id = v;
        novo->peso = peso;
        novo->prox = NULL;
     
        if (g->adj[u] == NULL) {
            g->adj[u] = novo;
        } else {
            no *aux = g->adj[u];
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
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
     
    void inicializa_single_source(grafo *g, int fonte, int *dist, int *pred) {
        for (int i = 0; i < g->vertices; i++) {
            dist[i] = INT_MAX;
            pred[i] = -1;
        }
        dist[fonte] = 0;
    }
     
    int relax(int v1, int v2, int peso, int *dist, int *pred) {
        if (dist[v1] == INT_MAX) {
            return 0;
        }
        if (dist[v2] > dist[v1] + peso) {
            dist[v2] = dist[v1] + peso;
            pred[v2] = v1;
            return 1;
        }
        return 0;
    }
     
    int bellman_ford(grafo *g, int s, int *dist, int *pred) {
        inicializa_single_source(g, s, dist, pred);
        for (int i = 0; i < g->vertices - 1; i++) {
            for (int u = 0; u < g->vertices; u++) {
                no *vizinho = g->adj[u];
                while (vizinho != NULL) {
                    relax(u, vizinho->id, vizinho->peso, dist, pred);
                    vizinho = vizinho->prox;
                }
            }
        }
        for (int u = 0; u < g->vertices; u++) {
            no *vizinho = g->adj[u];
            while (vizinho != NULL) {
                if (dist[u] != INT_MAX && dist[vizinho->id] > dist[u] + vizinho->peso) {
                    return 0;
                }
                vizinho = vizinho->prox;
            }
        }
        return 1;
    }
     
    void dijkstra(grafo *g, int fonte, int *dist, int *pred) {
        inicializa_single_source(g, fonte, dist, pred);
     
        fila *f = inicializa_fila(g->vertices);
        for (int i = 0; i < g->vertices; i++) {
            min_heap_insert(f, i, dist[i]);
        }
        while (f->tam_heap > 0) {
            Elemento e = min_heap_extract(f);
            int u = e.id;
            if (dist[u] != INT_MAX) {
                printf("%d %d\n", dist[u], pred[u]);
            }
            no *vizinho = g->adj[u];
            while (vizinho != NULL) {
                if (relax(u, vizinho->id, vizinho->peso, dist, pred) == 1) {
                    min_heap_decrease(f, vizinho->id, dist[vizinho->id]);
                }
                vizinho = vizinho->prox;
            }
        }
        desaloca_fila(f);
    }
     
    fila *inicializa_fila(int tam) {
        fila *f = malloc(sizeof(fila));
        if (f == NULL) {
            return NULL;
        }
     
        f->array = malloc(tam * sizeof(Elemento));
        f->mapa = malloc(tam * sizeof(int));
     
        if (f->array == NULL || f->mapa == NULL) {
            free(f->array);
            free(f->mapa);
            free(f);
            return NULL;
        }
     
        f->capacidade = tam;
        f->tam_heap = 0;
     
        for (int i = 0; i < tam; i++) {
            f->mapa[i] = -1;
        }
     
        return f;
    }
     
    void swap(fila *f, int i, int j) {
        Elemento temp = f->array[i];
        f->array[i] = f->array[j];
        f->array[j] = temp;
         
        //atualiza no vetor auxiliar as novas posições dos elementos na fila
        f->mapa[f->array[i].id] = i;
        f->mapa[f->array[j].id] = j;
    }
     
    void min_heap_insert(fila *f, int id, int chave) {
        if (f->tam_heap == f->capacidade) {
            return;
        }
        f->tam_heap++;
        int i = f->tam_heap - 1;
     
        f->array[i].id = id;
        f->array[i].chave = INT_MAX;
        f->mapa[id] = i; 
     
        min_heap_decrease(f, id, chave);
    }
     
    void min_heapify(fila *f, int i) {
        int l = left(i);
        int r = right(i);
        int menor = i;
     
        if (l < f->tam_heap && f->array[l].chave < f->array[menor].chave) {
            menor = l;
        }
        if (r < f->tam_heap && f->array[r].chave < f->array[menor].chave) {
            menor = r;
        }
     
        if (menor != i) {
            swap(f, i, menor);
            min_heapify(f, menor);
        }
    }
     
    void min_heap_decrease(fila *f, int id, int nova_chave) {
        int i = f->mapa[id];
     
        if (i < 0 || i >= f->tam_heap) {
            return;
        }
     
        if (nova_chave > f->array[i].chave) {
            return;
        }
     
        f->array[i].chave = nova_chave;
     
        while (i > 0 && f->array[i].chave < f->array[parent(i)].chave) {
            swap(f, i, parent(i));
            i = parent(i);
        }
    }
     
    Elemento min_heap_extract(fila *f) {
        if (f->tam_heap < 1) {
            Elemento erro = {-1, -1};
            return erro;
        }
        Elemento min = f->array[0];
     
        swap(f, 0, f->tam_heap - 1);
     
        f->tam_heap--;
     
        min_heapify(f, 0);
     
        return min;
    }
     
    void desaloca_fila(fila *f) {
        free(f->array);
        free(f->mapa);
        free(f);
    }
     
    int left(int i) {
        return (2 * i) + 1;
    }
     
    int right(int i) {
        return (2 * i) + 2;
    }
     
    int parent(int i) {
        return (i - 1) / 2;
    }
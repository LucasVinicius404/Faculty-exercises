#include <stdio.h>
#include <stdlib.h>

/**
 * @brief (PASSO 2 - Estruturas)
 * Define um nó da lista de adjacência.
 * Representa um vizinho de um vértice.
 */
typedef struct no {
    struct no *prox; // Ponteiro para o próximo vizinho
    int id;          // Rótulo/ID do vértice vizinho
} no;

/**
 * @brief (PASSO 2 - Estruturas)
 * Define a estrutura principal do Grafo.
 */
typedef struct grafo {
    struct no **adj; // Vetor de ponteiros (listas) de adjacência
    int vertices;    // Número total de vértices (N)
} grafo;

/**
 * @brief (PASSO 1 - Estruturas)
 * Define a Fila (Queue) para o BFS.
 * Implementada como um array circular.
 */
typedef struct fila {
    int *v;         // Vetor que armazena os IDs dos vértices na fila
    int cabeca;     // Índice de quem sai (dequeue)
    int final;      // Índice de onde entra (enqueue)
    int capacidade; // Tamanho máximo do vetor 'v'
} fila;

// --- Protótipos das Funções ---
grafo *inicializa_grafo(int vertices);
void adiciona_grafo(grafo *g, int v1, int v2);
void desaloca_grafo(grafo *g);
fila *inicializa_fila(int tam);
void insere_fila(fila *f, int vertice);
int remove_fila(fila *f);
void desaloca_fila(fila *f);
void bfs(grafo *g, int s, int *cor, int *dist, int *pred);
void imprime_caminho(int s, int v, int *pred);

// --- Função Principal ---
int main() {
    int vertices, arestas;

    // (PASSO 3) Leitura dos dados iniciais
    scanf("%d %d", &vertices, &arestas);

    // (PASSO 2) Cria a estrutura do grafo
    grafo *g = inicializa_grafo(vertices);

    // (PASSO 3) Laço para ler as M arestas e popular o grafo
    for (int i = 0; i < arestas; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        adiciona_grafo(g, v1, v2);
    }

    // (PASSO 3) Aloca os vetores de controle do BFS
    // 'cor' (0=branco, 1=cinza, 2=preto)
    // calloc já inicializa todos os N elementos com 0 (Branco)
    int *cor = calloc(vertices, sizeof(int));
    // 'distancia' (guarda a distância da fonte)
    int *distancia = malloc(vertices * sizeof(int));
    // 'predecessor' (guarda o "pai" de cada nó no caminho do BFS)
    int *predecessor = malloc(vertices * sizeof(int));

    // (PASSO 4) Executa o algoritmo BFS a partir da fonte 0
    bfs(g, 0, cor, distancia, predecessor);

    // (PASSO 6) Impressão final dos caminhos
    // Itera por todos os N vértices (0 a N-1)
    for (int i = 0; i < vertices; i++) {
        // Verifica se o vértice foi alcançado (distância != -1)
        if (distancia[i] == -1) {
            printf("Nao existe caminho de 0 a %d", i);
        } else {
            // (PASSO 5) Se foi alcançado, chama a função para imprimir o caminho
            imprime_caminho(0, i, predecessor);
        }
        printf("\n"); // Quebra de linha para o próximo vértice
    }

    // (PASSO 6) Limpeza de Memória
    desaloca_grafo(g);
    free(cor);
    free(distancia);
    free(predecessor);
    return 0;
}

/**
 * @brief (PASSO 2) Aloca memória para a estrutura do Grafo.
 */
grafo *inicializa_grafo(int vertices) {
    // Aloca a struct "contêiner" do grafo
    grafo *g = malloc(sizeof(grafo));
    if (g == NULL) {
        return NULL;
    }
    g->vertices = vertices;

    // Aloca o VETOR de PONTEIROS (as "cabeças" das listas)
    g->adj = malloc(vertices * sizeof(no *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }
    // Inicializa todas as listas de adjacência como vazias (NULL)
    for (int i = 0; i < vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

/**
 * @brief (PASSO 2) Adiciona uma aresta não direcionada {v1, v2} ao grafo.
 * Implementa a inserção NO FIM da lista (para bater com a saída do professor).
 */
void adiciona_grafo(grafo *g, int v1, int v2) {
    // --- Adiciona a aresta v1 -> v2 ---
    no *novo = malloc(sizeof(no));
    if (novo == NULL) return;
    novo->id = v2;
    novo->prox = NULL;

    // Se a lista de v1 estiver vazia, o novo nó é a cabeça
    if (g->adj[v1] == NULL) {
        g->adj[v1] = novo;
    } else {
        // Senão, percorre até o FIM da lista e insere
        no *p = g->adj[v1];
        while (p->prox != NULL) p = p->prox;
        p->prox = novo;
    }

    // --- Adiciona a aresta v2 -> v1 (porque é não direcionado) ---
    no *novo1 = malloc(sizeof(no));
    if (novo1 == NULL) return;
    novo1->id = v1;
    novo1->prox = NULL;

    // Se a lista de v2 estiver vazia, o novo nó é a cabeça
    if (g->adj[v2] == NULL) {
        g->adj[v2] = novo1;
    } else {
        // Senão, percorre até o FIM da lista e insere
        no *q = g->adj[v2];
        while (q->prox != NULL) q = q->prox;
        q->prox = novo1;
    }
}

/**
 * @brief (PASSO 6) Desaloca toda a memória usada pelo grafo.
 */
void desaloca_grafo(grafo *g) {
    // Itera por cada vértice
    for (int i = 0; i < g->vertices; i++) {
        no *remove = g->adj[i];
        // Percorre a lista de adjacência daquele vértice
        while (remove != NULL) {
            no *aux = remove;      // Guarda o nó atual
            remove = remove->prox; // Avança para o próximo
            free(aux);             // Libera o nó atual
        }
    }
    // Libera o vetor de ponteiros (as "linhas")
    free(g->adj);
    // Libera a struct "contêiner"
    free(g);
}

/**
 * @brief (PASSO 1) Aloca memória para a Fila.
 */
fila *inicializa_fila(int tam) {
    fila *f = malloc(sizeof(fila));
    if (f == NULL) {
        return NULL;
    }
    f->cabeca = f->final = 0;
    // Aloca tam+1 para a fila circular (guarda uma posição vazia)
    f->capacidade = tam + 1;
    f->v = malloc(f->capacidade * sizeof(int));
    if (f->v == NULL) {
        free(f);
        return NULL;
    }
    return f;
}

/**
 * @brief (PASSO 1) Adiciona um vértice (enqueue) na Fila.
 * Usa lógica de array circular.
 */
void insere_fila(fila *f, int vertice) {
    // Verifica se a fila está cheia
    if ((f->final + 1) % f->capacidade == f->cabeca) {
        return; // Fila cheia, não faz nada
    }
    // Insere no 'final' (cauda) e avança o ponteiro 'final'
    f->v[f->final] = vertice;
    f->final = (f->final + 1) % f->capacidade;
}

/**
 * @brief (PASSO 1) Remove um vértice (dequeue) da Fila.
 */
int remove_fila(fila *f) {
    // Verifica se a fila está vazia
    if (f->cabeca == f->final) {
        return -1; // Retorna -1 (ou erro) se vazia
    }
    // Pega o valor na 'cabeca'
    int u = f->v[f->cabeca];
    // Avança o ponteiro 'cabeca'
    f->cabeca = (f->cabeca + 1) % f->capacidade;
    return u;
}

/**
 * @brief (PASSO 1) Desaloca a memória da Fila.
 */
void desaloca_fila(fila *f) {
    free(f->v); // Libera o array interno
    free(f);    // Libera a struct
}

/**
 * @brief (PASSO 4) Executa a Busca em Largura (BFS).
 */
void bfs(grafo *g, int s, int *cor, int *dist, int *pred) {

    // Inicializa os vetores de controle para todos os vértices
    // (cor já foi inicializado com 0 (Branco) pelo calloc)
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = -1; // -1 representa "infinito"
        pred[i] = -1; // -1 representa "nulo"
    }

    // Inicializa a fonte 's' (vértice 0)
    cor[s] = 1;  // 1 = Cinza (descoberto)
    dist[s] = 0;
    // pred[s] já é -1

    // Cria a fila para o BFS
    fila *f = inicializa_fila(g->vertices);
    insere_fila(f, s); // Enfileira a fonte

    // Laço principal: enquanto a fila não estiver vazia
    while (f->cabeca != f->final) {
        // Desenfileira um vértice 'u'
        int u = remove_fila(f);
        // Pega a lista de vizinhos de 'u'
        no *vizinhos = g->adj[u];

        // Itera por todos os vizinhos de 'u'
        while (vizinhos != NULL) {
            int v = vizinhos->id; // 'v' é o vizinho atual

            // Se o vizinho 'v' for "Branco" (cor[v] == 0)
            if (cor[v] == 0) {
                cor[v] = 1;             // Pinta 'v' de Cinza
                dist[v] = dist[u] + 1;  // Define a distância
                pred[v] = u;            // Define 'u' como predecessor de 'v'
                insere_fila(f, v);      // Enfileira 'v' para ser visitado
            }
            vizinhos = vizinhos->prox; // Próximo vizinho
        }
        // Terminou de explorar 'u'
        cor[u] = 2; // Pinta 'u' de Preto (finalizado)
    }
    // Libera a fila usada pelo BFS
    desaloca_fila(f);
}

/**
 * @brief (PASSO 5) Imprime o caminho da fonte 's' até o destino 'v'.
 * Usa recursão para imprimir na ordem correta (frente para trás).
 */
void imprime_caminho(int s, int v, int *pred) {
    // Caso Base 1: Chegamos na fonte 's'
    if (v == s) {
        printf("-%d-", s);
        return; // Para a recursão
    }

    // Caso Base 2: O vértice não tem predecessor (proteção)
    if (pred[v] == -1) {
        return;
    }

    // Passo Recursivo: Chama a função para o predecessor (pai)
    imprime_caminho(s, pred[v], pred);

    // Imprime o vértice atual (só é executado APÓS a recursão retornar)
    printf("%d-", v);
}
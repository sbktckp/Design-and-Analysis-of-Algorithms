/*
 * 6.1 Prim MST
 *
 * Aim: given an undirected weighted connected graph G(V, E) and a starting
 *      vertex 's', maintain a min-priority queue over V and apply Prim's
 *      algorithm to find the minimum spanning tree T(V, E'). Display the cost
 *      adjacency matrix of T and its total cost.
 *
 * Input: "data/inUnAdjMat.dat" holds the cost adjacency matrix, one row per
 *        line, where 0 means there is no edge.
 *
 * Method: keep key[v] = weight of the cheapest known edge joining v to the
 *         growing tree, and parent[v] = the other end of that edge. Extract
 *         the minimum key, then relax its neighbours with DECREASE-KEY.
 *         With a binary heap that carries the position of every vertex, the
 *         cost is O(E log V).
 */
#include <stdio.h>
#include <stdlib.h>

#define NO_EDGE 0
#define INF 2147483647

/* Indexed min-priority queue: pos[] lets decrease_key find a vertex in O(1). */
struct min_pq {
    int *heap;      /* heap[i] = vertex at heap slot i          */
    int *pos;       /* pos[v]  = slot holding vertex v, or -1   */
    long *key;      /* key[v]  = priority of vertex v           */
    int size;
};

static void pq_swap(struct min_pq *q, int i, int j)
{
    int a = q->heap[i], b = q->heap[j];

    q->heap[i] = b;
    q->heap[j] = a;
    q->pos[b] = i;
    q->pos[a] = j;
}

static void pq_sift_up(struct min_pq *q, int i)
{
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (q->key[q->heap[parent]] <= q->key[q->heap[i]])
            return;
        pq_swap(q, parent, i);
        i = parent;
    }
}

static void pq_sift_down(struct min_pq *q, int i)
{
    for (;;) {
        int left = 2 * i + 1, right = left + 1, small = i;

        if (left < q->size && q->key[q->heap[left]] < q->key[q->heap[small]])
            small = left;
        if (right < q->size && q->key[q->heap[right]] < q->key[q->heap[small]])
            small = right;
        if (small == i)
            return;
        pq_swap(q, i, small);
        i = small;
    }
}

static int pq_extract_min(struct min_pq *q)
{
    int top = q->heap[0];

    q->pos[top] = -1;
    q->heap[0] = q->heap[--q->size];
    if (q->size > 0) {
        q->pos[q->heap[0]] = 0;
        pq_sift_down(q, 0);
    }
    return top;
}

static void pq_decrease_key(struct min_pq *q, int v, long value)
{
    q->key[v] = value;
    pq_sift_up(q, q->pos[v]);
}

static int pq_contains(const struct min_pq *q, int v)
{
    return q->pos[v] >= 0;
}

static int read_matrix(const char *path, int **matrix, int n)
{
    FILE *fp = fopen(path, "r");
    int i, j;

    if (fp == NULL) {
        perror(path);
        return 0;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (fscanf(fp, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "%s does not hold a %d by %d matrix\n", path, n, n);
                fclose(fp);
                return 0;
            }
    fclose(fp);
    return 1;
}

static int **alloc_matrix(int n)
{
    int **m = malloc((size_t)n * sizeof *m);
    int i;

    if (m == NULL)
        return NULL;
    for (i = 0; i < n; i++) {
        m[i] = calloc((size_t)n, sizeof **m);
        if (m[i] == NULL) {
            while (i-- > 0)
                free(m[i]);
            free(m);
            return NULL;
        }
    }
    return m;
}

static void free_matrix(int **m, int n)
{
    int i;

    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

int main(void)
{
    struct min_pq q;
    int **graph, **tree;
    int *parent;
    long total = 0;
    int n, start, i, j;

    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Vertex count must be a positive integer\n");
        return 1;
    }
    printf("Enter the Starting Vertex: ");
    if (scanf("%d", &start) != 1 || start < 1 || start > n) {
        fprintf(stderr, "Starting vertex must be between 1 and %d\n", n);
        return 1;
    }
    start--;                                    /* vertices are 0 based inside */

    graph = alloc_matrix(n);
    tree = alloc_matrix(n);
    parent = malloc((size_t)n * sizeof *parent);
    q.heap = malloc((size_t)n * sizeof *q.heap);
    q.pos = malloc((size_t)n * sizeof *q.pos);
    q.key = malloc((size_t)n * sizeof *q.key);
    if (graph == NULL || tree == NULL || parent == NULL
        || q.heap == NULL || q.pos == NULL || q.key == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    if (!read_matrix("data/inUnAdjMat.dat", graph, n))
        return 1;

    for (i = 0; i < n; i++) {
        q.key[i] = INF;
        parent[i] = -1;
        q.heap[i] = i;
        q.pos[i] = i;
    }
    q.size = n;
    pq_decrease_key(&q, start, 0);

    while (q.size > 0) {
        int u = pq_extract_min(&q);

        if (parent[u] >= 0) {
            tree[u][parent[u]] = graph[u][parent[u]];
            tree[parent[u]][u] = graph[u][parent[u]];
            total += graph[u][parent[u]];
        }
        for (j = 0; j < n; j++)
            if (graph[u][j] != NO_EDGE && pq_contains(&q, j)
                && graph[u][j] < q.key[j]) {
                parent[j] = u;
                pq_decrease_key(&q, j, graph[u][j]);
            }
    }

    printf("\nCost adjacency matrix of the minimum spanning tree:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%3d ", tree[i][j]);
        putchar('\n');
    }
    printf("\nSelected edges:\n");
    for (i = 0; i < n; i++)
        if (parent[i] >= 0)
            printf("  %d -- %d  cost %d\n", parent[i] + 1, i + 1, graph[i][parent[i]]);
    printf("\nTotal Weight of the Spanning Tree: %ld\n", total);

    free_matrix(graph, n);
    free_matrix(tree, n);
    free(parent);
    free(q.heap);
    free(q.pos);
    free(q.key);
    return 0;
}

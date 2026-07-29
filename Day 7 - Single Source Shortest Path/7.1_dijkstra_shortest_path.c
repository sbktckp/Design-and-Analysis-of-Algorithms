/*
 * 7.1 Dijkstra Shortest Path
 *
 * Aim: given a directed graph G(V, E) with non-negative weights and a source
 *      vertex 's', find the length of the shortest path from 's' to every
 *      other vertex and display the path itself.
 *
 * Input: "data/inDiAdjMat1.dat" holds the cost adjacency matrix, one row per
 *        line, where 0 means there is no edge.
 *
 * Method: keep a tentative distance for every vertex in a min-priority queue.
 *         Repeatedly settle the closest unsettled vertex and relax its
 *         outgoing edges. Non-negative weights are what make a settled vertex
 *         final. With an indexed binary heap the cost is O(E log V).
 */
#include <stdio.h>
#include <stdlib.h>

#define NO_EDGE 0
#define INF 2147483647L

struct min_pq {
    int *heap;
    int *pos;
    long *key;
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

static void print_path(const int *parent, int v)
{
    if (parent[v] >= 0) {
        print_path(parent, parent[v]);
        printf("->");
    }
    printf("%d", v + 1);
}

int main(void)
{
    const char *path = "data/inDiAdjMat1.dat";
    struct min_pq q;
    FILE *fp;
    int **graph;
    int *parent;
    long *dist;
    int n, source, i, j;

    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Vertex count must be a positive integer\n");
        return 1;
    }
    printf("Enter the Source Vertex: ");
    if (scanf("%d", &source) != 1 || source < 1 || source > n) {
        fprintf(stderr, "Source vertex must be between 1 and %d\n", n);
        return 1;
    }
    source--;

    graph = malloc((size_t)n * sizeof *graph);
    parent = malloc((size_t)n * sizeof *parent);
    dist = malloc((size_t)n * sizeof *dist);
    q.heap = malloc((size_t)n * sizeof *q.heap);
    q.pos = malloc((size_t)n * sizeof *q.pos);
    q.key = malloc((size_t)n * sizeof *q.key);
    if (graph == NULL || parent == NULL || dist == NULL
        || q.heap == NULL || q.pos == NULL || q.key == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        graph[i] = malloc((size_t)n * sizeof **graph);
        if (graph[i] == NULL) {
            fprintf(stderr, "Out of memory\n");
            return 1;
        }
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        perror(path);
        return 1;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (fscanf(fp, "%d", &graph[i][j]) != 1) {
                fprintf(stderr, "%s does not hold a %d by %d matrix\n", path, n, n);
                fclose(fp);
                return 1;
            }
    fclose(fp);

    for (i = 0; i < n; i++) {
        q.key[i] = INF;
        parent[i] = -1;
        q.heap[i] = i;
        q.pos[i] = i;
    }
    q.size = n;
    pq_decrease_key(&q, source, 0);

    while (q.size > 0) {
        int u = pq_extract_min(&q);

        dist[u] = q.key[u];
        if (dist[u] == INF)
            continue;                            /* unreachable from here on */
        for (j = 0; j < n; j++)
            if (graph[u][j] != NO_EDGE && pq_contains(&q, j)
                && dist[u] + graph[u][j] < q.key[j]) {
                parent[j] = u;
                pq_decrease_key(&q, j, dist[u] + graph[u][j]);
            }
    }

    printf("\n%-8s %-12s %-6s %s\n", "Source", "Destination", "Cost", "Path");
    for (i = 0; i < n; i++) {
        printf("%-8d %-12d ", source + 1, i + 1);
        if (dist[i] == INF) {
            printf("%-6s %s\n", "INF", "unreachable");
        } else if (i == source) {
            printf("%-6ld %s\n", dist[i], "-");
        } else {
            printf("%-6ld ", dist[i]);
            print_path(parent, i);
            putchar('\n');
        }
    }

    for (i = 0; i < n; i++)
        free(graph[i]);
    free(graph);
    free(parent);
    free(dist);
    free(q.heap);
    free(q.pos);
    free(q.key);
    return 0;
}

/*
 * 6.2 Kruskal MST
 *
 * Aim: given an undirected weighted connected graph G(V, E), apply Kruskal's
 *      algorithm to find the minimum spanning tree T(V, E'), display the
 *      selected edges and the total cost.
 *
 * Input: "data/inEdgeList.dat"
 *        first line   n m          vertices and edges
 *        next m lines u v w        an edge between u and v of weight w
 *
 * Method: sort every edge by weight, then walk the sorted list adding an edge
 *         only when its ends lie in different components. Disjoint-set with
 *         union by rank and path compression makes each test near constant,
 *         so the sort dominates at O(E log E).
 */
#include <stdio.h>
#include <stdlib.h>

struct edge {
    int u, v, w;
};

static int *parent, *rank_of;

static int find_set(int x)
{
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];          /* path compression */
        x = parent[x];
    }
    return x;
}

static int union_set(int a, int b)
{
    int ra = find_set(a), rb = find_set(b);

    if (ra == rb)
        return 0;                               /* already joined, a cycle */
    if (rank_of[ra] < rank_of[rb]) {
        parent[ra] = rb;
    } else if (rank_of[ra] > rank_of[rb]) {
        parent[rb] = ra;
    } else {
        parent[rb] = ra;
        rank_of[ra]++;
    }
    return 1;
}

static int cmp_edge(const void *x, const void *y)
{
    const struct edge *a = x, *b = y;

    if (a->w != b->w)
        return (a->w > b->w) - (a->w < b->w);
    if (a->u != b->u)
        return (a->u > b->u) - (a->u < b->u);
    return (a->v > b->v) - (a->v < b->v);
}

int main(void)
{
    const char *path = "data/inEdgeList.dat";
    FILE *fp = fopen(path, "r");
    struct edge *edges;
    long total = 0;
    int n, m, i, chosen = 0;

    if (fp == NULL) {
        perror(path);
        return 1;
    }
    if (fscanf(fp, "%d %d", &n, &m) != 2 || n <= 0 || m < 0) {
        fprintf(stderr, "First line must hold the vertex and edge counts\n");
        fclose(fp);
        return 1;
    }

    edges = malloc((size_t)m * sizeof *edges);
    parent = malloc((size_t)(n + 1) * sizeof *parent);
    rank_of = calloc((size_t)(n + 1), sizeof *rank_of);
    if (edges == NULL || parent == NULL || rank_of == NULL) {
        fprintf(stderr, "Out of memory\n");
        fclose(fp);
        return 1;
    }

    for (i = 0; i < m; i++)
        if (fscanf(fp, "%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
            fprintf(stderr, "%s holds fewer than %d edges\n", path, m);
            fclose(fp);
            return 1;
        }
    fclose(fp);

    printf("Vertices: %d   Edges: %d\n", n, m);
    for (i = 1; i <= n; i++)
        parent[i] = i;

    qsort(edges, (size_t)m, sizeof *edges, cmp_edge);

    printf("\nEdge      Cost\n");
    for (i = 0; i < m && chosen < n - 1; i++)
        if (union_set(edges[i].u, edges[i].v)) {
            printf("%d--%d      %d\n", edges[i].u, edges[i].v, edges[i].w);
            total += edges[i].w;
            chosen++;
        }

    if (chosen != n - 1)
        printf("\nThe graph is not connected, only %d of %d edges were chosen.\n",
               chosen, n - 1);
    printf("\nTotal Weight of the Spanning Tree: %ld\n", total);

    free(edges);
    free(parent);
    free(rank_of);
    return 0;
}

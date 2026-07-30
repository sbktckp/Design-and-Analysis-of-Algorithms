/*
 * 9.1 Floyd Warshall
 *
 * Aim: for a directed weighted graph, determine the shortest path length
 *      between every pair of vertices using Floyd-Warshall, and display the
 *      intermediate vertices on the shortest path of a given pair (u, v).
 *
 * Input: "data/inDiAdjMat2.dat" holds the cost adjacency matrix. A 0 off the
 *        diagonal means there is no edge. Negative weights are allowed, only
 *        negative cycles are not.
 *
 * Method: allow one more intermediate vertex k at every round and keep
 *         d[i][j] = min(d[i][j], d[i][k] + d[k][j]). The predecessor matrix
 *         is updated alongside so the path can be reconstructed.
 *         Time O(n^3), space O(n^2).
 */
#include <stdio.h>
#include <stdlib.h>

#define NO_EDGE 0
#define INF 1000000000L

static long **dist;
static int **pred;
static int n;

static void print_path(int u, int v)
{
    if (u == v) {
        printf("%d", u + 1);
        return;
    }
    if (pred[u][v] < 0) {
        printf("no path");
        return;
    }
    print_path(u, pred[u][v]);
    printf("-->%d", v + 1);
}

int main(void)
{
    const char *path = "data/inDiAdjMat2.dat";
    FILE *fp;
    int i, j, k, source, target, negative_cycle = 0;

    printf("Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Vertex count must be a positive integer\n");
        return 1;
    }

    dist = malloc((size_t)n * sizeof *dist);
    pred = malloc((size_t)n * sizeof *pred);
    if (dist == NULL || pred == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        dist[i] = malloc((size_t)n * sizeof **dist);
        pred[i] = malloc((size_t)n * sizeof **pred);
        if (dist[i] == NULL || pred[i] == NULL) {
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
        for (j = 0; j < n; j++) {
            int w;

            if (fscanf(fp, "%d", &w) != 1) {
                fprintf(stderr, "%s does not hold a %d by %d matrix\n", path, n, n);
                fclose(fp);
                return 1;
            }
            if (i == j) {
                dist[i][j] = 0;
                pred[i][j] = -1;
            } else if (w == NO_EDGE) {
                dist[i][j] = INF;
                pred[i][j] = -1;
            } else {
                dist[i][j] = w;
                pred[i][j] = i;
            }
        }
    fclose(fp);

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }

    for (i = 0; i < n; i++)
        if (dist[i][i] < 0)
            negative_cycle = 1;

    printf("\nShortest path weight matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dist[i][j] >= INF)
                printf("%5s", "INF");
            else
                printf("%5ld", dist[i][j]);
        }
        putchar('\n');
    }

    if (negative_cycle) {
        printf("\nThe graph contains a negative weight cycle, "
               "so the distances above are not meaningful.\n");
        return 0;
    }

    printf("\nEnter the source and destination vertex: ");
    if (scanf("%d %d", &source, &target) != 2
        || source < 1 || source > n || target < 1 || target > n) {
        fprintf(stderr, "Both vertices must be between 1 and %d\n", n);
        return 1;
    }
    source--;
    target--;

    printf("Path: ");
    if (dist[source][target] >= INF)
        printf("no path\n");
    else {
        print_path(source, target);
        printf("\nCost: %ld\n", dist[source][target]);
    }

    for (i = 0; i < n; i++) {
        free(dist[i]);
        free(pred[i]);
    }
    free(dist);
    free(pred);
    return 0;
}

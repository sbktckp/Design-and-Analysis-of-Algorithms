/*
 * Day 7, Q7.1  Dijkstra's shortest paths from one source
 *
 * Idea: d[v] is the best distance to v found so far, starting at infinity for
 * everything except the source at 0. Each round picks the unsettled vertex
 * with the smallest d, declares it settled, then relaxes its outgoing edges:
 * if going through u reaches j sooner than d[j], write down the shorter
 * distance and record u as j's parent.
 *
 * Settling is final because weights are not negative, so no later detour can
 * beat a distance that is already the smallest one left. Add a negative edge
 * and that argument collapses, which is why Day 9 needs a different algorithm.
 *
 * Input
 *   data/inDiAdjMat1.dat holds a 5 by 5 cost matrix, 0 meaning no edge
 *   Number of Vertices: 5
 *   Source Vertex: 1
 *
 * Output
 *   Source Destination Cost Path
 *   1 1 0 1
 *   1 2 8 1->4->2
 *   1 3 9 1->4->2->3
 *   1 4 5 1->4
 *   1 5 7 1->4->5
 *
 *   Note that reaching vertex 2 through vertex 4 costs 8, which beats the
 *   direct edge of 10. That is relaxation doing its job.
 */
#include <stdio.h>
int g[50][50], d[50], par[50], done[50], n;
void path(int v) { if (par[v] >= 0) { path(par[v]); printf("->"); } printf("%d", v + 1); }
int main() {
    FILE *f = fopen("../data/inDiAdjMat1.dat", "r");
    int s, i, j, u, best;
    printf("Number of Vertices: "); scanf("%d", &n);
    printf("Source Vertex: "); scanf("%d", &s);
    for (i = 0; i < n; i++) for (j = 0; j < n; j++) fscanf(f, "%d", &g[i][j]);
    for (i = 0; i < n; i++) { d[i] = 999999; par[i] = -1; }
    d[s - 1] = 0;
    for (i = 0; i < n; i++) {
        u = -1; best = 999999;
        for (j = 0; j < n; j++) if (!done[j] && d[j] < best) { best = d[j]; u = j; }
        if (u < 0) break;
        done[u] = 1;
        for (j = 0; j < n; j++)
            if (g[u][j] && d[u] + g[u][j] < d[j]) { d[j] = d[u] + g[u][j]; par[j] = u; }
    }
    printf("Source Destination Cost Path\n");
    for (i = 0; i < n; i++) {
        printf("%d %d %d ", s, i + 1, d[i]);
        path(i);
        printf("\n");
    }
    return 0;
}

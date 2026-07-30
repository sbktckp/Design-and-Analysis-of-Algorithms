/*
 * Day 6, Q6.1  Prim's minimum spanning tree
 *
 * Idea: grow one tree outwards from the starting vertex. key[v] holds the
 * cheapest single edge that would attach v to the tree so far, and par[v]
 * remembers the other end of that edge. Each round takes the unfinished vertex
 * with the smallest key, marks it done, then looks at its neighbours and
 * lowers their keys if this new vertex offers them a cheaper way in.
 *
 * After n rounds every vertex is attached, and the par[] array IS the tree.
 * The greedy choice is safe because the cheapest edge crossing out of the tree
 * can never be the wrong one to take.
 *
 * Input
 *   data/inUnAdjMat.dat holds a 9 by 9 cost matrix, 0 meaning no edge
 *   Number of Vertices: 9
 *   Starting Vertex: 1
 *
 * Output
 *   Selected edges:
 *   1 -- 2 cost 4
 *   6 -- 3 cost 4
 *   3 -- 4 cost 7
 *   4 -- 5 cost 9
 *   7 -- 6 cost 2
 *   8 -- 7 cost 1
 *   1 -- 8 cost 8
 *   3 -- 9 cost 2
 *   Total Weight: 37
 */
#include <stdio.h>
int g[50][50], key[50], par[50], done[50], n;
int main() {
    FILE *f = fopen("../data/inUnAdjMat.dat", "r");
    int s, i, j, u, best, tot = 0;
    printf("Number of Vertices: "); scanf("%d", &n);
    printf("Starting Vertex: "); scanf("%d", &s);
    for (i = 0; i < n; i++) for (j = 0; j < n; j++) fscanf(f, "%d", &g[i][j]);
    for (i = 0; i < n; i++) { key[i] = 999999; par[i] = -1; }
    key[s - 1] = 0;
    for (i = 0; i < n; i++) {
        u = -1; best = 999999;
        for (j = 0; j < n; j++) if (!done[j] && key[j] < best) { best = key[j]; u = j; }
        done[u] = 1; tot += key[u];
        for (j = 0; j < n; j++)
            if (g[u][j] && !done[j] && g[u][j] < key[j]) { key[j] = g[u][j]; par[j] = u; }
    }
    printf("Selected edges:\n");
    for (i = 0; i < n; i++) if (par[i] >= 0) printf("%d -- %d cost %d\n", par[i] + 1, i + 1, g[i][par[i]]);
    printf("Total Weight: %d\n", tot);
    return 0;
}

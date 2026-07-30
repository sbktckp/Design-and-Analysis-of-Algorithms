/*
 * Day 9, Q9.1  Floyd-Warshall, shortest path between every pair
 *
 * Idea: allow one more vertex to serve as a stopover on each pass. After the
 * pass for k, d[i][j] holds the best route from i to j that only stops at
 * vertices numbered up to k. So the test is simply: is going i to k and then k
 * to j shorter than what I have? Three nested loops and the whole all pairs
 * problem is solved.
 *
 * The k loop MUST be the outer one. Putting it inside gives a table that has
 * not considered every stopover set, and the answers come out wrong.
 *
 * Negative edge weights are fine here, unlike Dijkstra, because nothing is ever
 * declared final early. Only negative CYCLES break it, since you could then
 * loop forever getting cheaper.
 *
 * pr[i][j] holds the vertex just before j on the best route from i, so the
 * path is rebuilt by walking backwards. Note the update writes pr[k][j], not
 * k, which is what gives the whole chain rather than a single hop.
 *
 * Input
 *   data/inDiAdjMat2.dat holds a 5 by 5 matrix carrying a -4 and a -5
 *   Number of Vertices: 5
 *   Source and destination: 2 5
 *
 * Output
 *   Shortest path matrix:
 *       0    1   -3    2   -4
 *       3    0   -4    1   -1
 *       7    4    0    5    3
 *       2   -1   -5    0   -2
 *       8    5    1    6    0
 *   Path: 2-->4-->1-->5
 *   Cost: -1
 *
 *   Reading 2 to 5 as -1 shows the point: the direct edge costs 7, but going
 *   round through 4 and 1 picks up the -4 edge and ends up cheaper.
 */
#include <stdio.h>
int d[20][20], pr[20][20], n;
void path(int u, int v) {
    if (u == v) { printf("%d", u + 1); return; }
    path(u, pr[u][v]);
    printf("-->%d", v + 1);
}
int main() {
    FILE *f = fopen("../data/inDiAdjMat2.dat", "r");
    int i, j, k, w, s, t;
    printf("Number of Vertices: "); scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fscanf(f, "%d", &w);
            pr[i][j] = -1;
            if (i == j) d[i][j] = 0;
            else if (w == 0) d[i][j] = 9999;
            else { d[i][j] = w; pr[i][j] = i; }
        }
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) { d[i][j] = d[i][k] + d[k][j]; pr[i][j] = pr[k][j]; }
    printf("Shortest path matrix:\n");
    for (i = 0; i < n; i++) { for (j = 0; j < n; j++) printf("%5d", d[i][j]); printf("\n"); }
    printf("Source and destination: "); scanf("%d %d", &s, &t);
    printf("Path: "); path(s - 1, t - 1);
    printf("\nCost: %d\n", d[s - 1][t - 1]);
    return 0;
}

/*
 * Day 6, Q6.2  Kruskal's minimum spanning tree
 *
 * Idea: forget about growing one tree. Sort every edge from cheapest to
 * dearest and take each one unless it would close a cycle. Cheapest first is
 * the greedy part, and the cycle test is the whole trick.
 *
 * find(x) walks up the parent chain to the representative of x's component.
 * Two vertices are in the same component when they share a representative, so
 * an edge whose ends already agree would create a cycle and is skipped.
 * Joining two components is one assignment, p[a] = b.
 *
 * Input
 *   data/inEdgeList.dat starts with  9 14  then one line per edge, u v w
 *   No keyboard input needed
 *
 * Output
 *   Edge Cost
 *   7--8 1
 *   3--9 2
 *   6--7 2
 *   1--2 4
 *   3--6 4
 *   3--4 7
 *   1--8 8
 *   4--5 9
 *   Total Weight: 37
 *
 *   Same total as Prim's 37, though ties can be broken differently, so the
 *   list of edges is not always identical.
 */
#include <stdio.h>
int u[100], v[100], w[100], p[50];
int find(int x) { while (p[x] != x) x = p[x]; return x; }
int main() {
    FILE *f = fopen("../data/inEdgeList.dat", "r");
    int n, m, i, j, t, a, b, tot = 0;
    fscanf(f, "%d %d", &n, &m);
    for (i = 0; i < m; i++) fscanf(f, "%d %d %d", &u[i], &v[i], &w[i]);
    for (i = 0; i < m - 1; i++)
        for (j = i + 1; j < m; j++)
            if (w[j] < w[i]) {
                t = w[i]; w[i] = w[j]; w[j] = t;
                t = u[i]; u[i] = u[j]; u[j] = t;
                t = v[i]; v[i] = v[j]; v[j] = t;
            }
    for (i = 1; i <= n; i++) p[i] = i;
    printf("Edge Cost\n");
    for (i = 0; i < m; i++) {
        a = find(u[i]); b = find(v[i]);
        if (a != b) { p[a] = b; tot += w[i]; printf("%d--%d %d\n", u[i], v[i], w[i]); }
    }
    printf("Total Weight: %d\n", tot);
    return 0;
}

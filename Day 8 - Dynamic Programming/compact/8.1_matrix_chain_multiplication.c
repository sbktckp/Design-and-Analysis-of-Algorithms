/*
 * Day 8, Q8.1  Matrix chain multiplication
 *
 * Idea: matrix multiplication is associative, so the answer never changes, but
 * the cost does. Multiplying an a x b matrix by a b x c matrix costs a*b*c
 * scalar multiplications, so where you put the brackets matters enormously.
 *
 * m[i][j] is the cheapest cost of multiplying Ai through Aj. To fill it, try
 * every place k where the chain could be split, pay for the left part, the
 * right part, and the one multiplication that joins them, then keep the best.
 * s[i][j] remembers which k won, which is all the bracket printer needs.
 *
 * Chains are filled shortest first, L = 2 upwards, because a long chain leans
 * on shorter ones that must already be solved. That is the whole idea of
 * dynamic programming: solve small, reuse, never recompute.
 *
 * Dimensions live in p[], where matrix Ai is p[i-1] by p[i]. That is why the
 * cost term reads p[i-1] * p[k] * p[j].
 *
 * Input
 *   Number of matrices: 4
 *   Row and col of A1: 30 35
 *   Row and col of A2: 35 15
 *   Row and col of A3: 15 5
 *   Row and col of A4: 5 10
 *
 * Output
 *   M Table:
 *   0 15750 7875 9375
 *   0 0 2625 4375
 *   0 0 0 750
 *   0 0 0 0
 *   S Table:
 *   0 1 1 3
 *   0 0 2 3
 *   0 0 0 3
 *   0 0 0 0
 *   Optimal parenthesization: ((A1 (A2 A3)) A4)
 *   Scalar multiplications: 9375
 *
 *   Multiplying left to right would cost 87500, so the bracketing saves a lot.
 */
#include <stdio.h>
int m[20][20], s[20][20], p[20];
void br(int i, int j) {
    if (i == j) { printf("A%d", i); return; }
    printf("(");
    br(i, s[i][j]); printf(" "); br(s[i][j] + 1, j);
    printf(")");
}
int main() {
    int n, i, j, k, L, c;
    printf("Number of matrices: "); scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        printf("Row and col of A%d: ", i);
        scanf("%d %d", &j, &k);
        if (i == 1) p[0] = j;
        p[i] = k;
    }
    for (L = 2; L <= n; L++)
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1; m[i][j] = -1;
            for (k = i; k < j; k++) {
                c = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (m[i][j] < 0 || c < m[i][j]) { m[i][j] = c; s[i][j] = k; }
            }
        }
    printf("M Table:\n");
    for (i = 1; i <= n; i++) { for (j = 1; j <= n; j++) printf("%d ", m[i][j]); printf("\n"); }
    printf("S Table:\n");
    for (i = 1; i <= n; i++) { for (j = 1; j <= n; j++) printf("%d ", s[i][j]); printf("\n"); }
    printf("Optimal parenthesization: "); br(1, n);
    printf("\nScalar multiplications: %d\n", m[1][n]);
    return 0;
}

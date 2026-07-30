/*
 * Day 5, Q5.2  Huffman tree
 *
 * Idea: take the two rarest symbols, join them under a new node whose
 * frequency is their sum, and drop that node back into the pool. Repeat n-1
 * times and one node is left, the root. Rare symbols end up deep, so their
 * codes are long, and common symbols stay shallow with short codes.
 *
 * The tree lives in three arrays. Index i has frequency fq[i], left child
 * lf[i] and right child rt[i], where -1 means no child, so a node with lf[i]
 * equal to -1 is a leaf carrying a real alphabet. used[] marks nodes already
 * pulled out of the pool.
 *
 * The in-order walk prints left subtree, then the node, then right subtree,
 * but only prints leaves, since internal nodes hold sums rather than letters.
 *
 * Input
 *   Number of distinct alphabets: 6
 *   Alphabets: a b c d e f
 *   Frequencies: 45 13 12 16 9 5
 *
 * Output
 *   In-order traversal (Huffman): a c b f e d
 *
 *   Working: f5 and e9 join into 14, c12 and b13 join into 25, 14 and d16 join
 *   into 30, 25 and 30 join into 55, then a45 and 55 join into the root 100.
 */
#include <stdio.h>
int fq[100], lf[100], rt[100], used[100], n, m;
char ch[100];
int mn() {
    int i, b = -1;
    for (i = 0; i < m; i++) if (!used[i] && (b < 0 || fq[i] < fq[b])) b = i;
    return b;
}
void in(int i) {
    if (i < 0) return;
    in(lf[i]);
    if (lf[i] < 0) printf("%c ", ch[i]);
    in(rt[i]);
}
int main() {
    int i, x, y;
    printf("Number of distinct alphabets: "); scanf("%d", &n);
    printf("Alphabets: ");
    for (i = 0; i < n; i++) scanf(" %c", &ch[i]);
    printf("Frequencies: ");
    for (i = 0; i < n; i++) { scanf("%d", &fq[i]); lf[i] = rt[i] = -1; }
    m = n;
    for (i = 0; i < n - 1; i++) {
        x = mn(); used[x] = 1;
        y = mn(); used[y] = 1;
        fq[m] = fq[x] + fq[y]; lf[m] = x; rt[m] = y; m++;
    }
    printf("In-order traversal (Huffman): ");
    in(m - 1);
    printf("\n");
    return 0;
}

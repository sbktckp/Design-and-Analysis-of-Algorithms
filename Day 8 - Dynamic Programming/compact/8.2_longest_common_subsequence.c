/*
 * Day 8, Q8.2  Longest common subsequence
 *
 * Idea: c[i][j] is the LCS length of the first i characters of x and the first
 * j of y. Two cases, and that is the entire algorithm:
 *   the characters match, so take the diagonal answer and add one
 *   they do not match, so drop one character from whichever side helps more
 *
 * A subsequence keeps order but may skip characters, which is why this is not
 * the same as a common substring.
 *
 * Reading the answer back out means walking from the bottom right corner. On a
 * match, that character belongs to the LCS, so record it and step diagonally.
 * Otherwise step whichever way the table came from. The characters arrive
 * backwards, so they are written into out[] from the end towards the front.
 *
 * Input
 *   First string: 10010101
 *   Second string: 010110110
 *
 * Output
 *   LCS: 100110
 *   LCS Length: 6
 *
 *   Several different subsequences also have length 6. Any one of them is a
 *   correct answer.
 */
#include <stdio.h>
#include <string.h>
int c[200][200];
int main() {
    char x[200], y[200], out[200];
    int i, j, m, n, k;
    printf("First string: "); scanf("%199s", x);
    printf("Second string: "); scanf("%199s", y);
    m = strlen(x); n = strlen(y);
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            if (x[i - 1] == y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = c[i - 1][j] >= c[i][j - 1] ? c[i - 1][j] : c[i][j - 1];
    k = c[m][n]; out[k] = 0;
    i = m; j = n;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) { out[--k] = x[i - 1]; i--; j--; }
        else if (c[i - 1][j] >= c[i][j - 1]) i--;
        else j--;
    }
    printf("LCS: %s\nLCS Length: %d\n", out, c[m][n]);
    return 0;
}

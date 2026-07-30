/*
 * 8.2 Longest Common Subsequence
 *
 * Aim: find the longest common subsequence of two given strings and print its
 *      length.
 *
 * Method: dynamic programming. c[i][j] is the LCS length of the first i
 *         characters of X and the first j of Y. Equal characters extend the
 *         diagonal, otherwise the better of the two neighbours wins. The
 *         subsequence itself is recovered by walking the table backwards.
 *         Time O(mn), space O(mn).
 *
 * When several subsequences share the maximum length, this recovery reports
 * one of them, which is all the definition asks for.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

int main(void)
{
    static char x[MAX_LEN], y[MAX_LEN];
    int **c;
    int m, n, i, j, len;
    char *lcs;

    printf("Enter the first string into an array: ");
    if (scanf("%1023s", x) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("Enter the second string into an array: ");
    if (scanf("%1023s", y) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    m = (int)strlen(x);
    n = (int)strlen(y);

    c = malloc((size_t)(m + 1) * sizeof *c);
    if (c == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }
    for (i = 0; i <= m; i++) {
        c[i] = calloc((size_t)(n + 1), sizeof **c);
        if (c[i] == NULL) {
            fprintf(stderr, "Out of memory\n");
            return 1;
        }
    }

    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else if (c[i - 1][j] >= c[i][j - 1])
                c[i][j] = c[i - 1][j];
            else
                c[i][j] = c[i][j - 1];
        }

    len = c[m][n];
    lcs = malloc((size_t)len + 1);
    if (lcs == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }
    lcs[len] = '\0';

    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            lcs[--len] = x[i - 1];
            i--;
            j--;
        } else if (c[i - 1][j] >= c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", c[m][n]);

    for (i = 0; i <= m; i++)
        free(c[i]);
    free(c);
    free(lcs);
    return 0;
}

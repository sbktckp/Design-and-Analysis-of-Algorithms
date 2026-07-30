/*
 * 8.1 Matrix Chain Multiplication
 *
 * Aim: find the optimal parenthesization of a matrix chain product using the
 *      M-table and S-table, and print the number of scalar multiplications
 *      the optimal ordering needs. Dimension compatibility is validated.
 *
 * Method: dynamic programming over chain length. m[i][j] is the cheapest cost
 *         of multiplying Ai..Aj, s[i][j] remembers the split point that
 *         achieved it. Time O(n^3), space O(n^2).
 */
#include <stdio.h>
#include <stdlib.h>

static int **alloc_int_matrix(int n)
{
    int **m = malloc((size_t)n * sizeof *m);
    int i;

    if (m == NULL)
        return NULL;
    for (i = 0; i < n; i++) {
        m[i] = calloc((size_t)n, sizeof **m);
        if (m[i] == NULL) {
            while (i-- > 0)
                free(m[i]);
            free(m);
            return NULL;
        }
    }
    return m;
}

static void free_int_matrix(int **m, int n)
{
    int i;

    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

static void print_table(const char *title, int **t, int n)
{
    int i, j;

    printf("%s\n", title);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%d ", t[i][j]);
        putchar('\n');
    }
}

static void print_parenthesization(int **s, int i, int j)
{
    if (i == j) {
        printf("A%d", i);
        return;
    }
    printf("(");
    print_parenthesization(s, i, s[i][j]);
    printf(" ");
    print_parenthesization(s, s[i][j] + 1, j);
    printf(")");
}

int main(void)
{
    int **m, **s;
    int *p;                                 /* p[0..n], dimensions */
    int n, i, j, len, k;

    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Matrix count must be a positive integer\n");
        return 1;
    }

    p = malloc((size_t)(n + 1) * sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    for (i = 1; i <= n; i++) {
        int rows, cols;

        printf("Enter row and col size of A%d: ", i);
        if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
            fprintf(stderr, "Dimensions must be positive integers\n");
            free(p);
            return 1;
        }
        if (i == 1) {
            p[0] = rows;
        } else if (rows != p[i - 1]) {
            fprintf(stderr,
                    "Dimension mismatch: A%d has %d columns but A%d has %d rows\n",
                    i - 1, p[i - 1], i, rows);
            free(p);
            return 1;
        }
        p[i] = cols;
    }

    m = alloc_int_matrix(n + 1);
    s = alloc_int_matrix(n + 1);
    if (m == NULL || s == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(p);
        return 1;
    }

    for (len = 2; len <= n; len++)
        for (i = 1; i <= n - len + 1; i++) {
            j = i + len - 1;
            m[i][j] = -1;
            for (k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (m[i][j] < 0 || cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }

    putchar('\n');
    print_table("M Table:", m, n);
    putchar('\n');
    print_table("S Table:", s, n);

    printf("\nOptimal parenthesization: ");
    print_parenthesization(s, 1, n);
    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n",
           m[1][n]);

    free_int_matrix(m, n + 1);
    free_int_matrix(s, n + 1);
    free(p);
    return 0;
}

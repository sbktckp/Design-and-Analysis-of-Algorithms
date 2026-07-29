/*
 * 1.4 Rotate Right Array
 *
 * Aim: write ROTATE_RIGHT(p1, p2) that rotates the first p2 elements of an
 *      array right by one position, using EXCHANGE(p, q) to swap two numbers.
 *      p1 is the starting address of the array, p2 the count of elements
 *      to be rotated.
 *
 * Method: swap adjacent pairs from the back towards the front, which carries
 *      the last element of the block to the front. Time O(p2), space O(1).
 */
#include <stdio.h>
#include <stdlib.h>

static void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

static void ROTATE_RIGHT(int *p1, int p2)
{
    int i;
    for (i = p2 - 1; i > 0; i--)
        EXCHANGE(&p1[i], &p1[i - 1]);
}

static void print_array(const char *label, const int *a, int n)
{
    int i;
    printf("%s", label);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    putchar('\n');
}

int main(void)
{
    int n, k, i;
    int *a;

    printf("Size of the array (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "N must be a positive integer\n");
        return 1;
    }

    a = malloc((size_t)n * sizeof *a);
    if (a == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    printf("Enter an array A of size N (%d): ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(a);
            return 1;
        }
    }

    printf("Number of elements to rotate (p2): ");
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        fprintf(stderr, "p2 must be between 1 and %d\n", n);
        free(a);
        return 1;
    }

    print_array("Before ROTATE: ", a, n);
    ROTATE_RIGHT(a, k);
    print_array("After  ROTATE: ", a, n);

    free(a);
    return 0;
}

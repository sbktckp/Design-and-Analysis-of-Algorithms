/*
 * 10.1 Randomized Quicksort
 *
 * Aim: implement randomized quicksort and explain its expected time
 *      complexity.
 *
 * Method: RANDOMIZED-PARTITION swaps a uniformly chosen element into the
 *         pivot slot before running the usual Lomuto partition. Deterministic
 *         quicksort degrades to O(n^2) on sorted input because the pivot is
 *         always extreme. Choosing the pivot at random makes the split depend
 *         on the coin rather than on the data, so the expected number of
 *         comparisons is 2n ln n, roughly 1.39 n log2 n, for EVERY input.
 *         No input is a worst case any more, only unlucky randomness is, and
 *         the probability of that is vanishingly small.
 *
 * The program sorts an already sorted array, the input that ruins the
 * deterministic version, and reports the comparison count next to both
 * theoretical bounds so the difference is visible.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long long comparisons;
static int max_depth;

static void swap(int *p, int *q)
{
    int t = *p;
    *p = *q;
    *q = t;
}

static int partition(int *a, int lo, int hi)
{
    int pivot = a[hi], i = lo - 1, j;

    for (j = lo; j < hi; j++) {
        comparisons++;
        if (a[j] <= pivot)
            swap(&a[++i], &a[j]);
    }
    swap(&a[i + 1], &a[hi]);
    return i + 1;
}

static int randomized_partition(int *a, int lo, int hi)
{
    int r = lo + rand() % (hi - lo + 1);

    swap(&a[r], &a[hi]);
    return partition(a, lo, hi);
}

static void randomized_quicksort(int *a, int lo, int hi, int depth)
{
    int q;

    if (depth > max_depth)
        max_depth = depth;
    if (lo >= hi)
        return;
    q = randomized_partition(a, lo, hi);
    randomized_quicksort(a, lo, q - 1, depth + 1);
    randomized_quicksort(a, q + 1, hi, depth + 1);
}

int main(void)
{
    int *a, n, i, sorted = 1;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Element count must be a positive integer\n");
        return 1;
    }

    a = malloc((size_t)n * sizeof *a);
    if (a == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        a[i] = (i + 1) * 10;                 /* already sorted, the hard case */

    srand((unsigned)time(NULL));
    comparisons = 0;
    max_depth = 0;
    randomized_quicksort(a, 0, n - 1, 1);

    for (i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            sorted = 0;

    printf("\nInput was already sorted, %d elements\n", n);
    printf("Output verified sorted    : %s\n", sorted ? "yes" : "no");
    printf("Comparisons made          : %lld\n", comparisons);
    printf("Maximum recursion depth   : %d\n", max_depth);
    printf("Expected 1.39 n log2 n    : %.0f\n", 1.39 * n * log2((double)n));
    printf("Deterministic worst case  : %.0f\n", (double)n * (n - 1) / 2.0);
    printf("\nExpected time complexity: O(n log n) on every input, because the\n"
           "pivot rank is uniform, not data dependent. Worst case is still\n"
           "O(n^2) but it now needs pathological luck rather than sorted input.\n");

    free(a);
    return 0;
}

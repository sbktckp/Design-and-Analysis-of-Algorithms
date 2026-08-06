/*
 * 3.3 Min and Max
 *
 * Aim: find the minimum and the maximum element of an array using the divide
 *      and conquer method, and count the comparisons actually made.
 *
 * Method: split the range in half, find the min and max of each half by
 *         calling yourself, then combine with just two comparisons. The base
 *         cases stop the recursion: one element is its own min and max at a
 *         cost of zero comparisons, two elements need exactly one.
 *
 *         The straightforward loop needs 2(n-1) comparisons, one against the
 *         running minimum and one against the running maximum for every
 *         element. Divide and conquer needs about 3n/2 - 2, which is a quarter
 *         fewer, because pairing the elements up front means each pair costs
 *         one comparison to order and then two to merge, rather than two each.
 *
 * Both counts are printed side by side so the saving is visible.
 */
#include <stdio.h>
#include <stdlib.h>

static long long comparisons;

struct pair {
    int min;
    int max;
};

static struct pair min_max(const int *a, int lo, int hi)
{
    struct pair result, left, right;
    int mid;

    if (lo == hi) {                     /* one element, no comparison needed */
        result.min = a[lo];
        result.max = a[lo];
        return result;
    }
    if (hi == lo + 1) {                 /* two elements, exactly one         */
        comparisons++;
        if (a[lo] < a[hi]) {
            result.min = a[lo];
            result.max = a[hi];
        } else {
            result.min = a[hi];
            result.max = a[lo];
        }
        return result;
    }

    mid = lo + (hi - lo) / 2;
    left = min_max(a, lo, mid);
    right = min_max(a, mid + 1, hi);

    comparisons++;                      /* two comparisons to combine */
    result.min = (left.min < right.min) ? left.min : right.min;
    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main(void)
{
    const char *path = "data/3.3_input.txt";
    FILE *fp;
    struct pair answer;
    int *a, n, i;

    printf("Size of the array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    a = malloc((size_t)n * sizeof *a);
    if (a == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        perror(path);
        fprintf(stderr, "Run this from inside the day folder, or use ./run 3.3\n");
        free(a);
        return 1;
    }
    for (i = 0; i < n; i++)
        if (fscanf(fp, "%d", &a[i]) != 1) {
            fprintf(stderr, "%s holds fewer than %d integers\n", path, n);
            fclose(fp);
            free(a);
            return 1;
        }
    fclose(fp);

    printf("Array read from file: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    putchar('\n');

    comparisons = 0;
    answer = min_max(a, 0, n - 1);

    printf("\nMinimum element: %d\n", answer.min);
    printf("Maximum element: %d\n", answer.max);
    printf("\nComparisons made           : %lld\n", comparisons);
    printf("A simple loop would need    : %d\n", 2 * (n - 1));
    printf("Theoretical 3n/2 - 2        : %d\n", (3 * n) / 2 - 2);

    free(a);
    return 0;
}

/*
 * 3.4 Binary Search
 *
 * Aim: search a sorted array for a key and report the position of its
 *      LEFTMOST appearance, along with the number of comparisons made.
 *
 * Method: halve the search range each step. Compare the key with the middle
 *         element: equal or smaller means the answer cannot be to the right,
 *         so keep the left half INCLUDING the middle; larger means discard
 *         the middle and everything left of it.
 *
 *         Note the difference from the ordinary version. Plain binary search
 *         stops the moment it finds a match, which with duplicates lands on
 *         an arbitrary one. Keeping the middle in play on equality drives the
 *         range down to the FIRST match instead, at the cost of never being
 *         able to stop early. So the count is always about log2(n).
 *
 * Positions are printed 0 based, matching the sample on the sheet where 7 in
 * 2 3 7 7 7 11 12 12 20 50 is found at index 2.
 */
#include <stdio.h>
#include <stdlib.h>

static long long comparisons;

/* Returns the index of the leftmost element equal to key, or -1. */
static int binary_search_first(const int *a, int n, int key)
{
    int lo = 0, hi = n - 1, mid, answer = -1;

    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;       /* written this way to avoid overflow */
        comparisons++;
        if (a[mid] == key) {
            answer = mid;
            hi = mid - 1;               /* an earlier one may still exist */
        } else if (a[mid] < key) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return answer;
}

static int is_sorted(const int *a, int n)
{
    int i;

    for (i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return 0;
    return 1;
}

int main(void)
{
    int *a, n, i, key, found;

    printf("Enter size of array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Size must be a positive integer\n");
        return 1;
    }

    a = malloc((size_t)n * sizeof *a);
    if (a == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    printf("Enter elements of the array in ascending order: ");
    for (i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(a);
            return 1;
        }

    if (!is_sorted(a, n)) {
        fprintf(stderr, "The array is not sorted. Binary search needs sorted input.\n");
        free(a);
        return 1;
    }

    printf("Enter the key to be searched: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(a);
        return 1;
    }

    comparisons = 0;
    found = binary_search_first(a, n, key);

    if (found < 0)
        printf("\n%d not found in the array\n", key);
    else
        printf("\n%d found at index position %d\n", key, found);
    printf("Number of comparisons: %lld\n", comparisons);

    free(a);
    return 0;
}

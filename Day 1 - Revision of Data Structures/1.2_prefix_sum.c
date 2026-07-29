/*
 * 1.2 Prefix Sum Array
 *
 * Aim: given an array arr[] of size N, build prefixSum[] such that
 *      prefixSum[i] = arr[0] + arr[1] + ... + arr[i].
 *
 * Method: running total in one pass. Time O(n), space O(n) for the output.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, i;
    int *arr, *prefix;

    printf("Size of the array (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "N must be a positive integer\n");
        return 1;
    }

    arr    = malloc((size_t)n * sizeof *arr);
    prefix = malloc((size_t)n * sizeof *prefix);
    if (arr == NULL || prefix == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(arr);
        free(prefix);
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            free(prefix);
            return 1;
        }
    }

    prefix[0] = arr[0];
    for (i = 1; i < n; i++)
        prefix[i] = prefix[i - 1] + arr[i];

    printf("Input Array : ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nOutput Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", prefix[i]);
    putchar('\n');

    free(arr);
    free(prefix);
    return 0;
}

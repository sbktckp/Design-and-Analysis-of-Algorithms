/*
 * 1.3 Duplicate Element Count
 *
 * Aim: read 'n' integers from a disc file into an array, then report
 *      (a) the total number of duplicate elements (values occurring more
 *          than once), and
 *      (b) the most repeating element.
 *
 * Method: sort a copy, then scan equal runs. Time O(n log n), space O(n).
 *         Beats the naive O(n^2) pairwise comparison.
 */
#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *x, const void *y)
{
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

int main(void)
{
    const char *path = "data/1.3_input.txt";
    FILE *fp;
    int n, i;
    int *arr, *sorted;
    int duplicates = 0, best_value = 0, best_count = 0;

    printf("Enter how many numbers you want to read from file: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Count must be a positive integer\n");
        return 1;
    }

    arr    = malloc((size_t)n * sizeof *arr);
    sorted = malloc((size_t)n * sizeof *sorted);
    if (arr == NULL || sorted == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(arr);
        free(sorted);
        return 1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        perror(path);
        free(arr);
        free(sorted);
        return 1;
    }
    for (i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "File holds fewer than %d integers\n", n);
            fclose(fp);
            free(arr);
            free(sorted);
            return 1;
        }
        sorted[i] = arr[i];
    }
    fclose(fp);

    qsort(sorted, (size_t)n, sizeof *sorted, cmp_int);

    for (i = 0; i < n; ) {
        int j = i;
        while (j < n && sorted[j] == sorted[i])
            j++;
        if (j - i > 1)
            duplicates++;
        if (j - i > best_count) {
            best_count = j - i;
            best_value = sorted[i];
        }
        i = j;
    }

    printf("The content of the array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nTotal number of duplicate values = %d\n", duplicates);
    printf("The most repeating element in the array = %d (%d times)\n",
           best_value, best_count);

    free(arr);
    free(sorted);
    return 0;
}

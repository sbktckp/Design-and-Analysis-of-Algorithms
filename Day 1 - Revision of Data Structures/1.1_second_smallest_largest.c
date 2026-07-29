/*
 * 1.1 Second Smallest & Largest
 *
 * Aim: read 'n' integers from a disc file and find the second smallest
 *      and the second largest element of the array.
 *
 * Method: one pass maintaining the two smallest and two largest distinct
 *         values. Time O(n), space O(1) - no array storage needed.
 */
#include <stdio.h>

int main(void)
{
    const char *path = "data/1.1_input.txt";
    FILE *fp;
    int n, i, x;
    /* min1 < min2 are the smallest two distinct values, max1 > max2 the largest two */
    long min1 = 0, min2 = 0, max1 = 0, max2 = 0;
    int seen_min2 = 0, seen_max2 = 0;

    printf("Size of the array (n): ");
    if (scanf("%d", &n) != 1 || n < 2) {
        fprintf(stderr, "n must be an integer >= 2\n");
        return 1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        perror(path);
        return 1;
    }

    printf("Array read from file: ");
    for (i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &x) != 1) {
            fprintf(stderr, "\nFile holds fewer than %d integers\n", n);
            fclose(fp);
            return 1;
        }
        printf("%d ", x);

        if (i == 0) {
            min1 = max1 = x;
            continue;
        }
        if (x < min1) {
            min2 = min1;
            seen_min2 = 1;
            min1 = x;
        } else if (x > min1 && (!seen_min2 || x < min2)) {
            min2 = x;
            seen_min2 = 1;
        }
        if (x > max1) {
            max2 = max1;
            seen_max2 = 1;
            max1 = x;
        } else if (x < max1 && (!seen_max2 || x > max2)) {
            max2 = x;
            seen_max2 = 1;
        }
    }
    fclose(fp);

    putchar('\n');
    if (!seen_min2 || !seen_max2) {
        printf("All elements are equal - no second smallest/largest exists\n");
        return 0;
    }
    printf("Second smallest: %ld\n", min2);
    printf("Second largest : %ld\n", max2);
    return 0;
}

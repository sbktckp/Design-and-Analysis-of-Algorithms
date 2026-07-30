/*
 * Day 1, Q1.1  Second smallest and second largest
 *
 * Idea: sort the array in ascending order, then the second smallest is at
 * index 1 and the second largest is at index n-2. Bubble sort is used because
 * it is four lines, not because it is fast.
 *
 * Input
 *   data/1.1_input.txt holds:  23 5 47 5 12 89 47 3 66 31
 *   Size of the array (n): 10
 *
 * Output
 *   Second smallest: 5
 *   Second largest: 66
 */
#include <stdio.h>
int main() {
    FILE *f = fopen("../data/1.1_input.txt", "r");
    int n, i, j, t, a[100];
    printf("Size of the array (n): ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) fscanf(f, "%d", &a[i]);
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (a[i] > a[j]) { t = a[i]; a[i] = a[j]; a[j] = t; }
    printf("Second smallest: %d\n", a[1]);
    printf("Second largest: %d\n", a[n - 2]);
    return 0;
}

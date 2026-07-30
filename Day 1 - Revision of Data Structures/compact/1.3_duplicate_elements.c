/*
 * Day 1, Q1.3  Duplicate count and most repeating element
 *
 * Idea: for each element, first check whether the same value appeared earlier.
 * If it did, skip it, so every distinct value is handled exactly once. Then
 * count how many times it occurs. A count above 1 means it is a duplicate
 * value, and the largest count wins the most repeating title.
 *
 * Input
 *   data/1.3_input.txt holds:  10 40 35 47 68 22 40 10 98 10 50 35 68 40 10
 *   How many numbers to read from file: 15
 *
 * Output
 *   Total number of duplicate values = 4
 *   The most repeating element = 10
 */
#include <stdio.h>
int main() {
    FILE *f = fopen("../data/1.3_input.txt", "r");
    int n, i, j, c, dup = 0, best = 0, bc = 0, a[100];
    printf("How many numbers to read from file: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) fscanf(f, "%d", &a[i]);
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) if (a[j] == a[i]) break;
        if (j < i) continue;
        c = 0;
        for (j = 0; j < n; j++) if (a[j] == a[i]) c++;
        if (c > 1) dup++;
        if (c > bc) { bc = c; best = a[i]; }
    }
    printf("Total number of duplicate values = %d\n", dup);
    printf("The most repeating element = %d\n", best);
    return 0;
}

/*
 * Day 1, Q1.2  Prefix sum array
 *
 * Idea: prefixSum[i] is prefixSum[i-1] plus arr[i], so one running total in a
 * single loop does the whole job. The first entry is just arr[0].
 *
 * Input
 *   Size of the array (N): 5
 *   Enter 5 elements: 3 4 5 1 2
 *
 * Output
 *   Output Array: 3 7 12 13 15
 */
#include <stdio.h>
int main() {
    int n, i, a[100], p[100];
    printf("Size of the array (N): ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    p[0] = a[0];
    for (i = 1; i < n; i++) p[i] = p[i - 1] + a[i];
    printf("Output Array: ");
    for (i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
    return 0;
}

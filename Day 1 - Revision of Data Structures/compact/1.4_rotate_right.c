/*
 * Day 1, Q1.4  Rotate the first p2 elements right by one
 *
 * Idea: walk from the end of the block towards the front, swapping each
 * neighbouring pair. That carries the last element of the block to the front
 * one step at a time, and everything else slides right by one. EXCHANGE is
 * the swap the question asks for.
 *
 * Input
 *   Size of array (N): 9
 *   Enter 9 elements: 11 22 33 44 55 66 77 88 99
 *   Elements to rotate (p2): 5
 *
 * Output
 *   Before ROTATE: 11 22 33 44 55 66 77 88 99
 *   After ROTATE: 55 11 22 33 44 66 77 88 99
 */
#include <stdio.h>
void EXCHANGE(int *p, int *q) { int t = *p; *p = *q; *q = t; }
void ROTATE_RIGHT(int *p1, int p2) {
    int i;
    for (i = p2 - 1; i > 0; i--) EXCHANGE(&p1[i], &p1[i - 1]);
}
int main() {
    int n, k, i, a[100];
    printf("Size of array (N): ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Elements to rotate (p2): ");
    scanf("%d", &k);
    printf("Before ROTATE: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    ROTATE_RIGHT(a, k);
    printf("\nAfter ROTATE: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

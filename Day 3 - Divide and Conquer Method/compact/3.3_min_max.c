/*
 * Day 3, Q3.3  Minimum and maximum by divide and conquer
 *
 * Idea: split the range in half, get the min and max of each half by calling
 * yourself, then combine with two comparisons. One element needs no
 * comparison at all, two elements need exactly one, and those two base cases
 * are what make it cheaper than a plain loop.
 *
 * A simple loop compares every element twice, against the running min and the
 * running max, so 2(n-1) in total. This does about 3n/2 - 2, a quarter fewer,
 * because pairing elements up front costs one comparison per pair instead of
 * two per element.
 *
 * Input
 *   data/3.3_input.txt holds:  45 12 78 3 99 23 67 5 88 34 91 7 56 19 72
 *   Size of the array (n): 15
 *
 * Output
 *   Minimum element: 3
 *   Maximum element: 99
 *   Comparisons: 21
 *   A simple loop would need: 28
 */
#include <stdio.h>
int a[200], mn, mx;
long cmp = 0;
void minmax(int lo, int hi, int *lmn, int *lmx) {
    int m, a1, a2, b1, b2;
    if (lo == hi) { *lmn = *lmx = a[lo]; return; }
    if (hi == lo + 1) {
        cmp++;
        if (a[lo] < a[hi]) { *lmn = a[lo]; *lmx = a[hi]; }
        else { *lmn = a[hi]; *lmx = a[lo]; }
        return;
    }
    m = (lo + hi) / 2;
    minmax(lo, m, &a1, &a2);
    minmax(m + 1, hi, &b1, &b2);
    cmp++; *lmn = a1 < b1 ? a1 : b1;
    cmp++; *lmx = a2 > b2 ? a2 : b2;
}
int main() {
    FILE *f = fopen("../data/3.3_input.txt", "r");
    int n, i;
    printf("Size of the array (n): ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) fscanf(f, "%d", &a[i]);
    minmax(0, n - 1, &mn, &mx);
    printf("Minimum element: %d\n", mn);
    printf("Maximum element: %d\n", mx);
    printf("Comparisons: %ld\n", cmp);
    printf("A simple loop would need: %d\n", 2 * (n - 1));
    return 0;
}

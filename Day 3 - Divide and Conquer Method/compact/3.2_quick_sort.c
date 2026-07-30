/*
 * Day 3, Q3.2  Quick sort with a comparison count and a case verdict
 *
 * Idea: pick the last element as pivot, sweep the range moving everything not
 * greater than the pivot to the left, then drop the pivot between the two
 * sides. Sort each side by calling yourself. Unlike merge sort, the split
 * depends entirely on the data, which is what makes the two verdicts differ.
 *
 * Sorted input is the worst case here, because the pivot is always the largest
 * element, so one side gets n-1 items and the other gets none. That is
 * n(n-1)/2 comparisons. Shuffled input splits near the middle and lands near
 * n log n.
 *
 * Input
 *   1 Ascending 2 Descending 3 Random
 *   Enter option: 1
 *
 * Output
 *   After Sorting: 10 20 30 ... 3000
 *   Comparisons: 44850
 *   Scenario: Worst case
 *
 *   Option 3 gives 2719 comparisons and prints Best case.
 *   For 300 elements, 44850 is exactly 300 x 299 / 2.
 */
#include <stdio.h>
int a[600];
long cmp = 0;
int part(int lo, int hi) {
    int p = a[hi], i = lo - 1, j, t;
    for (j = lo; j < hi; j++) {
        cmp++;
        if (a[j] <= p) { i++; t = a[i]; a[i] = a[j]; a[j] = t; }
    }
    t = a[i + 1]; a[i + 1] = a[hi]; a[hi] = t;
    return i + 1;
}
void qsortx(int lo, int hi) {
    int q;
    if (lo >= hi) return;
    q = part(lo, hi);
    qsortx(lo, q - 1); qsortx(q + 1, hi);
}
int main() {
    char *name[] = {"../data/inAsce.dat", "../data/inDesc.dat", "../data/inRand.dat"};
    int opt, n = 0, i;
    FILE *f;
    printf("1 Ascending 2 Descending 3 Random\nEnter option: ");
    scanf("%d", &opt);
    f = fopen(name[opt - 1], "r");
    while (fscanf(f, "%d", &a[n]) == 1) n++;
    qsortx(0, n - 1);
    printf("After Sorting: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nComparisons: %ld\n", cmp);
    printf("Scenario: %s case\n", cmp > (long)n * 20 ? "Worst" : "Best");
    return 0;
}

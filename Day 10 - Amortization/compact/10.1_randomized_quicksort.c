/*
 * Day 10, Q10.1  Randomized quicksort
 *
 * Idea: ordinary quicksort dies on sorted input, because the last element is
 * always the largest, so every split is n-1 against 0 and the cost becomes
 * O(n^2). Swap a randomly chosen element into the pivot slot first and the
 * split no longer depends on the input order at all, only on the dice.
 *
 * That is why the expected cost is O(n log n) for EVERY input. There is still a
 * worst case, but it now needs a run of terrible luck rather than a particular
 * input, and the chance of that is negligible.
 *
 * This program deliberately feeds it the killer input, an already sorted array,
 * to show the difference in the count.
 *
 * Input
 *   Number of elements: 300
 *
 * Output
 *   Sorted 300 already sorted elements
 *   Comparisons: 2514
 *   Deterministic worst case would be: 44850
 *
 *   The exact number changes every run, since the pivots are random. It stays
 *   in the low thousands, nowhere near 44850.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[1000];
long cmp = 0;
void qs(int lo, int hi) {
    int i = lo - 1, j, r, t, p;
    if (lo >= hi) return;
    r = lo + rand() % (hi - lo + 1);
    t = a[r]; a[r] = a[hi]; a[hi] = t;
    p = a[hi];
    for (j = lo; j < hi; j++) { cmp++; if (a[j] <= p) { i++; t = a[i]; a[i] = a[j]; a[j] = t; } }
    t = a[i + 1]; a[i + 1] = a[hi]; a[hi] = t;
    qs(lo, i); qs(i + 2, hi);
}
int main() {
    int n, i;
    printf("Number of elements: "); scanf("%d", &n);
    for (i = 0; i < n; i++) a[i] = (i + 1) * 10;
    srand(time(0));
    qs(0, n - 1);
    printf("Sorted %d already sorted elements\nComparisons: %ld\n", n, cmp);
    printf("Deterministic worst case would be: %d\n", n * (n - 1) / 2);
    return 0;
}

/*
 * Day 3, Q3.1  Merge sort with a comparison count
 *
 * Idea: split the range in half, sort both halves by calling yourself, then
 * walk the two sorted halves side by side copying the smaller front element
 * into a scratch array. Every comparison happens in that walk, so counting
 * there counts them all. The work is O(n log n) whatever order the input is
 * in, which is why the count barely changes between the three files.
 *
 * Input
 *   1 Ascending 2 Descending 3 Random
 *   Enter option: 3
 *   data/inRand.dat holds 300 shuffled multiples of 10
 *
 * Output
 *   After Sorting: 10 20 30 40 ... 3000
 *   Elements: 300
 *   Comparisons: 2114
 *
 *   Option 1 gives 1717 comparisons, option 2 gives 1500. Merge sort does
 *   nearly the same work every time.
 */
#include <stdio.h>
int a[600], t[600];
long cmp = 0;
void merge(int lo, int m, int hi) {
    int i = lo, j = m + 1, k = lo;
    while (i <= m && j <= hi) { cmp++; t[k++] = (a[i] <= a[j]) ? a[i++] : a[j++]; }
    while (i <= m) t[k++] = a[i++];
    while (j <= hi) t[k++] = a[j++];
    for (i = lo; i <= hi; i++) a[i] = t[i];
}
void msort(int lo, int hi) {
    int m = (lo + hi) / 2;
    if (lo >= hi) return;
    msort(lo, m); msort(m + 1, hi); merge(lo, m, hi);
}
int main() {
    char *name[] = {"../data/inAsce.dat", "../data/inDesc.dat", "../data/inRand.dat"};
    int opt, n = 0, i;
    FILE *f;
    printf("1 Ascending 2 Descending 3 Random\nEnter option: ");
    scanf("%d", &opt);
    f = fopen(name[opt - 1], "r");
    while (fscanf(f, "%d", &a[n]) == 1) n++;
    msort(0, n - 1);
    printf("After Sorting: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nElements: %d\nComparisons: %ld\n", n, cmp);
    return 0;
}

/*
 * Day 3, Q3.4  Binary search, leftmost appearance
 *
 * Idea: halve the range each step. If the middle equals the key, remember the
 * position but KEEP LOOKING to the left, since an earlier copy may exist. If
 * the middle is smaller, the answer must be to the right. If bigger, to the
 * left.
 *
 * That one change, hi = mid - 1 instead of stopping on a match, is the whole
 * difference between ordinary binary search and this. Ordinary binary search
 * returns whichever duplicate it happens to land on. It also means the loop
 * can never finish early, so the count is always about log2(n).
 *
 * The array must be sorted. Binary search on unsorted data gives wrong
 * answers quietly rather than crashing.
 *
 * Input
 *   Enter size of array: 10
 *   Enter elements of the array: 2 3 7 7 7 11 12 12 20 50
 *   Enter the key to be searched: 7
 *
 * Output
 *   7 found at index position 2
 *   Number of comparisons: 3
 *
 *   Index 2 is the FIRST of the three sevens, not index 3 or 4. Searching for
 *   8 prints not found, also after 3 comparisons.
 */
#include <stdio.h>
int main() {
    int a[200], n, i, key, lo, hi, mid, ans = -1;
    long cmp = 0;
    printf("Enter size of array: ");
    scanf("%d", &n);
    printf("Enter elements of the array: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Enter the key to be searched: ");
    scanf("%d", &key);
    lo = 0; hi = n - 1;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        cmp++;
        if (a[mid] == key) { ans = mid; hi = mid - 1; }
        else if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    if (ans < 0) printf("%d not found\n", key);
    else printf("%d found at index position %d\n", key, ans);
    printf("Number of comparisons: %ld\n", cmp);
    return 0;
}

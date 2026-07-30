/*
 * Day 5, Q5.1  Fractional knapsack
 *
 * Idea: value density decides everything. Work out profit divided by weight
 * for each item, put the densest first, then walk the list taking whole items
 * while they fit and a fraction of the one that does not. Greedy is provably
 * optimal here because leftover capacity can always be filled with a slice,
 * which is exactly what fails in the 0/1 version.
 *
 * Input
 *   Number of items: 3
 *   Profit and weight of item 1: 27 16
 *   Profit and weight of item 2: 14 12
 *   Profit and weight of item 3: 26 13
 *   Capacity: 18
 *
 * Output
 *   Item Profit Weight Taken
 *   3 26.00 13.00 1.000000
 *   1 27.00 16.00 0.312500
 *   2 14.00 12.00 0.000000
 *   Maximum profit: 34.437500
 *
 *   Item 3 has the best ratio, 2.00, so it goes in whole. That leaves 5 of the
 *   18 capacity, and 5/16 of item 1 is 0.3125.
 */
#include <stdio.h>
int main() {
    double pr[50], wt[50], rt[50], cap, take, total = 0, x;
    int n, i, j, id[50], k;
    printf("Number of items: "); scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Profit and weight of item %d: ", i + 1);
        scanf("%lf %lf", &pr[i], &wt[i]);
        rt[i] = pr[i] / wt[i]; id[i] = i + 1;
    }
    printf("Capacity: "); scanf("%lf", &cap);
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (rt[j] > rt[i]) {
                x = rt[i]; rt[i] = rt[j]; rt[j] = x;
                x = pr[i]; pr[i] = pr[j]; pr[j] = x;
                x = wt[i]; wt[i] = wt[j]; wt[j] = x;
                k = id[i]; id[i] = id[j]; id[j] = k;
            }
    printf("Item Profit Weight Taken\n");
    for (i = 0; i < n; i++) {
        take = (wt[i] <= cap) ? 1 : (cap > 0 ? cap / wt[i] : 0);
        cap -= take * wt[i]; total += take * pr[i];
        printf("%d %.2f %.2f %.6f\n", id[i], pr[i], wt[i], take);
    }
    printf("Maximum profit: %.6f\n", total);
    return 0;
}

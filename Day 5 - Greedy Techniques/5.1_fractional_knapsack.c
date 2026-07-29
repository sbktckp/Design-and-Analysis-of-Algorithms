/*
 * 5.1 Fractional Knapsack
 *
 * Aim: find the maximum profit that does not exceed the given knapsack
 *      capacity using the Fractional Knapsack algorithm. Items are sorted in
 *      non-increasing order of profit/weight using Heap Sort.
 *
 * Method: greedy. Once items are ordered by value density, taking as much of
 *         the densest item as fits is optimal for the fractional problem.
 *         Heap sort costs O(n log n), the greedy sweep O(n).
 *
 * Heap sort detail: building a MIN-heap and repeatedly moving the smallest
 * ratio to the end of the array leaves the array in non-increasing order,
 * which is exactly the order the greedy step wants.
 */
#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;
};

static void swap_item(struct ITEM *a, struct ITEM *b)
{
    struct ITEM t = *a;
    *a = *b;
    *b = t;
}

static void min_heapify(struct ITEM *a, int n, int i)
{
    for (;;) {
        int left = 2 * i + 1, right = left + 1, small = i;

        if (left < n && a[left].profit_weight_ratio < a[small].profit_weight_ratio)
            small = left;
        if (right < n && a[right].profit_weight_ratio < a[small].profit_weight_ratio)
            small = right;
        if (small == i)
            return;
        swap_item(&a[i], &a[small]);
        i = small;
    }
}

static void heap_sort_desc(struct ITEM *a, int n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
        min_heapify(a, n, i);
    for (i = n - 1; i > 0; i--) {
        swap_item(&a[0], &a[i]);            /* smallest ratio to the back */
        min_heapify(a, i, 0);
    }
}

int main(void)
{
    struct ITEM *items;
    double capacity, remaining, total_profit = 0.0;
    int n, i;

    printf("Enter the number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Number of items must be a positive integer\n");
        return 1;
    }
    items = malloc((size_t)n * sizeof *items);
    if (items == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        if (scanf("%lf %lf", &items[i].item_profit, &items[i].item_weight) != 2
            || items[i].item_weight <= 0.0) {
            fprintf(stderr, "Profit and a positive weight are required\n");
            free(items);
            return 1;
        }
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    if (scanf("%lf", &capacity) != 1 || capacity < 0.0) {
        fprintf(stderr, "Capacity must be a non-negative number\n");
        free(items);
        return 1;
    }

    heap_sort_desc(items, n);
    remaining = capacity;

    printf("\n%-9s %-12s %-12s %s\n", "Item No", "profit", "Weight", "Amount to be taken");
    for (i = 0; i < n; i++) {
        double taken = 0.0;

        if (remaining > 0.0) {
            if (items[i].item_weight <= remaining)
                taken = 1.0;
            else
                taken = remaining / items[i].item_weight;
            remaining -= taken * items[i].item_weight;
            total_profit += taken * items[i].item_profit;
        }
        printf("%-9d %-12f %-12f %f\n", items[i].item_id,
               items[i].item_profit, items[i].item_weight, taken);
    }
    printf("Maximum profit: %f\n", total_profit);

    free(items);
    return 0;
}

/* 4.2 Fractional Knapsack - compact: read, sort by ratio, fill, print profit. */
#include <stdio.h>
#include <stdlib.h>

struct item { double weight, profit, ratio; };

static int cmp(const void *a, const void *b)
{
    double ra = ((const struct item *)a)->ratio, rb = ((const struct item *)b)->ratio;
    return (ra < rb) - (ra > rb);
}

int main(void)
{
    struct item items[64];
    int n = 0;
    double capacity, remaining, profit = 0.0;
    FILE *fp = fopen("data/inKnapsack.dat", "r");

    if (fp == NULL) {
        perror("data/inKnapsack.dat");
        return 1;
    }
    while (n < 64 && fscanf(fp, "%lf,%lf", &items[n].weight, &items[n].profit) == 2) {
        items[n].ratio = items[n].profit / items[n].weight;
        n++;
    }
    fclose(fp);

    printf("Enter knapsack capacity: ");
    if (scanf("%lf", &capacity) != 1)
        return 1;

    qsort(items, (size_t)n, sizeof *items, cmp);
    remaining = capacity;
    for (int i = 0; i < n && remaining > 0.0; i++) {
        if (items[i].weight <= remaining) {
            remaining -= items[i].weight;
            profit += items[i].profit;
        } else {
            profit += (remaining / items[i].weight) * items[i].profit;
            remaining = 0.0;
        }
    }
    printf("Maximum profit obtainable: %.2f\n", profit);
    return 0;
}

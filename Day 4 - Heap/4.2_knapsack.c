/*
 * 4.2 Fractional Knapsack
 *
 * Aim: read 'n' items (weight, profit) from a file into a dynamically
 *      allocated array, then fill a knapsack of a given capacity to
 *      maximize total profit, taking fractions of items where needed.
 *
 * File format, one record per line:
 *      weight,profit
 *
 * Method: greedy on profit/weight ratio. Sort items by ratio, descending,
 *         then take whole items until one no longer fits, then take
 *         whatever fraction of that item still fits. O(n log n) for the
 *         sort, O(n) for the fill.
 */
#include <stdio.h>
#include <stdlib.h>

struct item {
    int id;
    double weight;
    double profit;
    double ratio;
};

static struct item *items;
static int count;

static void free_items(void)
{
    free(items);
    items = NULL;
    count = 0;
}

static void print_table(const char *title)
{
    int i;

    printf("%s\n", title);
    printf("%-4s %-10s %-10s %s\n", "Id", "Weight", "Profit", "Ratio");
    for (i = 0; i < count; i++)
        printf("%-4d %-10.2f %-10.2f %.4f\n", items[i].id, items[i].weight,
               items[i].profit, items[i].ratio);
}

static void read_data(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[128];
    int cap = 0;
    int id = 0;

    if (fp == NULL) {
        perror(path);
        return;
    }
    free_items();

    while (fgets(line, sizeof line, fp) != NULL) {
        struct item it;
        double weight, profit;

        if (sscanf(line, "%lf,%lf", &weight, &profit) != 2)
            continue;
        it.id = id++;
        it.weight = weight;
        it.profit = profit;
        it.ratio = (weight != 0.0) ? profit / weight : 0.0;

        if (count == cap) {
            struct item *grown;
            cap = (cap == 0) ? 8 : cap * 2;
            grown = realloc(items, (size_t)cap * sizeof *items);
            if (grown == NULL) {
                fprintf(stderr, "Out of memory\n");
                break;
            }
            items = grown;
        }
        items[count++] = it;
    }
    fclose(fp);

    if (count == 0) {
        printf("No records read from %s\n", path);
        return;
    }
    print_table("Data read from file:");
}

static int by_ratio_desc(const void *a, const void *b)
{
    double ra = ((const struct item *)a)->ratio;
    double rb = ((const struct item *)b)->ratio;

    if (ra < rb)
        return 1;
    if (ra > rb)
        return -1;
    return 0;
}

static void fill_knapsack(double capacity)
{
    double remaining = capacity;
    double total_profit = 0.0;
    int i;

    qsort(items, (size_t)count, sizeof *items, by_ratio_desc);
    print_table("Items sorted by profit/weight ratio:");

    printf("\nSelection for capacity %.2f:\n", capacity);
    for (i = 0; i < count && remaining > 0.0; i++) {
        if (items[i].weight <= remaining) {
            remaining -= items[i].weight;
            total_profit += items[i].profit;
            printf("Item %d: take whole, weight %.2f, profit %.2f\n",
                   items[i].id, items[i].weight, items[i].profit);
        } else {
            double fraction = remaining / items[i].weight;
            total_profit += fraction * items[i].profit;
            printf("Item %d: take fraction %.4f, weight %.2f, profit %.2f\n",
                   items[i].id, fraction, remaining, fraction * items[i].profit);
            remaining = 0.0;
        }
    }
    printf("\nMaximum profit obtainable: %.2f\n", total_profit);
}

int main(void)
{
    int option;

    for (;;) {
        printf("\nMAIN MENU (FRACTIONAL KNAPSACK)\n"
               "1. Read Data\n"
               "2. Fill Knapsack (enter capacity)\n"
               "3. Exit\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            break;

        if (option == 2 && count == 0) {
            printf("No data in memory. Choose option 1 first.\n");
            continue;
        }

        switch (option) {
        case 1:
            read_data("data/inKnapsack.dat");
            break;
        case 2: {
            double capacity;
            printf("Enter knapsack capacity: ");
            if (scanf("%lf", &capacity) != 1)
                break;
            fill_knapsack(capacity);
            break;
        }
        case 3:
            free_items();
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
    free_items();
    return 0;
}

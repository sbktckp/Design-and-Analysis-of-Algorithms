/*
 * 10.3 Binary Counter Reset
 *
 * Aim: store a binary counter in an array of bits and support INCREMENT and
 *      RESET so that any sequence of n operations on an initially zero
 *      counter costs O(n) time in total. Examining or changing one bit costs
 *      1 unit.
 *
 * Method: as the hint says, keep a pointer to the high-order 1. RESET then
 *         clears only the bits up to that pointer instead of the whole array,
 *         so its cost is proportional to how much INCREMENT actually built up.
 *
 *         Potential function  PHI = (number of 1 bits) + (high + 1).
 *           INCREMENT clears t trailing ones and sets one bit, costing t + 1,
 *           while PHI falls by t - 1 and rises by at most 1, so the amortized
 *           cost is at most 3.
 *           RESET costs high + 2 and drives PHI down by at least high + 1, so
 *           its amortized cost is at most 1.
 *         Both are O(1) amortized, hence O(n) for n operations.
 */
#include <stdio.h>

#define BITS 32

static int bit[BITS];
static int high = -1;               /* index of the high-order 1, -1 if zero */
static long long total_cost;

static void show(const char *operation, long long cost)
{
    int i;

    for (i = BITS - 1; i >= 0; i--)
        if (i <= high || i < 8)                 /* always show the low byte */
            printf("%d", bit[i]);
    printf("   %-10s cost %-4lld total %lld\n", operation, cost, total_cost);
}

static long long increment(void)
{
    long long cost = 0;
    int i = 0;

    while (i < BITS && bit[i] == 1) {           /* flip the trailing ones */
        bit[i] = 0;
        cost++;
        i++;
    }
    if (i == BITS) {
        printf("Counter overflow\n");
        return cost;
    }
    bit[i] = 1;
    cost++;
    if (i > high)
        high = i;
    total_cost += cost;
    return cost;
}

static long long reset(void)
{
    long long cost = 1;                         /* reading the pointer */
    int i;

    for (i = 0; i <= high; i++) {
        bit[i] = 0;
        cost++;
    }
    high = -1;
    total_cost += cost;
    return cost;
}

int main(void)
{
    int option;

    printf("Binary counter with INCREMENT and RESET, %d bits\n", BITS);
    show("Initial", 0);

    for (;;) {
        printf("\nMAIN MENU (BINARY COUNTER)\n"
               "1. Increment\n"
               "2. Reset\n"
               "3. Display\n"
               "4. Run the sample sequence\n"
               "5. Exit\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            return 0;

        switch (option) {
        case 1:
            show("Increment", increment());
            break;
        case 2:
            show("Reset", reset());
            break;
        case 3:
            show("Display", 0);
            break;
        case 4: {
            int i;

            for (i = 0; i < BITS; i++)
                bit[i] = 0;
            high = -1;
            total_cost = 0;
            printf("\nBit pattern (low 8 bits shown)   Operation  Cost\n");
            show("Initial", 0);
            show("Increment", increment());
            show("Increment", increment());
            show("Reset", reset());
            show("Increment", increment());
            show("Reset", reset());
            printf("Total cost of 5 operations: %lld, which is O(n)\n", total_cost);
            break;
        }
        case 5:
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
}

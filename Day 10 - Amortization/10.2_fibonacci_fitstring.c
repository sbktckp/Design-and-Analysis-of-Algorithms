/*
 * 10.2 Fibonacci Fitstring
 *
 * Aim: represent an integer as a sum of Fibonacci numbers, an array of fits
 *      rather than bits, where the ith fit says whether Fi is included, and
 *      support increment and decrement in constant amortized time.
 *
 *      The fitstring 101110 is F6 + F4 + F3 + F2 = 8 + 3 + 2 + 1 = 14.
 *      Fits are indexed from 2 upwards, since F1 and F2 are both 1.
 *
 * Method: as the hint says, a number may have several fitstrings, so the
 *         representation is kept redundant and repaired locally.
 *           carry    a[i] = 2      ->  2*Fi = F(i+1) + F(i-2)
 *           combine  a[i] = a[i+1] = 1  ->  Fi + F(i+1) = F(i+2)
 *           borrow   Fi = F(i-1) + F(i-2)
 *         Each repair is O(1) work and lowers the potential function
 *         "number of set fits plus number of adjacent set pairs", so a long
 *         chain of repairs is paid for by the cheap operations that built it.
 *         Amortized cost per increment or decrement is therefore O(1).
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_FIT 80

static int fit[MAX_FIT + 3];        /* fit[2] is the least significant */
static unsigned long long fib[MAX_FIT + 3];
static long long repairs;           /* work done by the last operation */

static void build_fib(void)
{
    int i;

    fib[1] = 1;
    fib[2] = 1;
    for (i = 3; i <= MAX_FIT + 2; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
}

static unsigned long long value(void)
{
    unsigned long long sum = 0;
    int i;

    for (i = 2; i <= MAX_FIT; i++)
        sum += (unsigned long long)fit[i] * fib[i];
    return sum;
}

static void show(void)
{
    int i, high = 2;

    for (i = MAX_FIT; i >= 2; i--)
        if (fit[i] != 0) {
            high = i;
            break;
        }
    printf("value = %-6llu fitstring = ", value());
    for (i = high; i >= 2; i--)
        printf("%d", fit[i]);
    printf("   (repairs: %lld)\n", repairs);
}

/* Pushes the representation back to fits of 0 and 1 with no adjacent pair. */
static void normalize(void)
{
    int changed = 1, i;

    while (changed) {
        changed = 0;
        for (i = 2; i <= MAX_FIT; i++) {
            if (fit[i] >= 2) {
                repairs++;
                changed = 1;
                if (i == 2) {                   /* 2*F2 = F3            */
                    fit[2] -= 2;
                    fit[3] += 1;
                } else if (i == 3) {            /* 2*F3 = F4 + F2       */
                    fit[3] -= 2;
                    fit[4] += 1;
                    fit[2] += 1;
                } else {                        /* 2*Fi = F(i+1) + F(i-2) */
                    fit[i] -= 2;
                    fit[i + 1] += 1;
                    fit[i - 2] += 1;
                }
            } else if (fit[i] == 1 && fit[i + 1] == 1) {   /* Fi + F(i+1) */
                repairs++;
                changed = 1;
                fit[i] = 0;
                fit[i + 1] = 0;
                fit[i + 2] += 1;
            }
        }
    }
}

static int lowest_set(void)
{
    int i;

    for (i = 2; i <= MAX_FIT; i++)
        if (fit[i] > 0)
            return i;
    return -1;
}

static void increment(void)
{
    repairs = 0;
    fit[2] += 1;                                /* F2 = 1 */
    normalize();
}

static int decrement(void)
{
    int i;

    repairs = 0;
    if (lowest_set() < 0)
        return 0;                               /* already zero */

    /* Borrow downwards until a fit worth 1 or 2 is available. */
    while ((i = lowest_set()) > 3) {
        repairs++;
        fit[i] -= 1;
        fit[i - 1] += 1;
        fit[i - 2] += 1;                        /* Fi = F(i-1) + F(i-2) */
    }
    i = lowest_set();
    if (i == 2) {
        fit[2] -= 1;
    } else {                                    /* F3 = 2, leave one behind */
        fit[3] -= 1;
        fit[2] += 1;
    }
    normalize();
    return 1;
}

static void self_test(int upto)
{
    unsigned long long expected;
    int i, ok = 1;

    for (i = 2; i <= MAX_FIT; i++)
        fit[i] = 0;

    for (expected = 1; expected <= (unsigned long long)upto; expected++) {
        increment();
        if (value() != expected)
            ok = 0;
    }
    for (expected = (unsigned long long)upto; expected > 0; expected--) {
        if (value() != expected)
            ok = 0;
        decrement();
    }
    if (value() != 0)
        ok = 0;
    printf("Self test over 0 to %d and back: %s\n", upto, ok ? "PASSED" : "FAILED");
}

int main(void)
{
    int option;

    build_fib();
    for (;;) {
        printf("\nMAIN MENU (FIBONACCI FITSTRING)\n"
               "1. Increment\n"
               "2. Decrement\n"
               "3. Display value and fitstring\n"
               "4. Run self test\n"
               "5. Exit\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            return 0;

        switch (option) {
        case 1:
            increment();
            show();
            break;
        case 2:
            if (!decrement())
                printf("Value is already zero\n");
            else
                show();
            break;
        case 3:
            repairs = 0;
            show();
            break;
        case 4: {
            int upto;
            printf("Count up to: ");
            if (scanf("%d", &upto) != 1 || upto <= 0)
                break;
            self_test(upto);
            break;
        }
        case 5:
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
}

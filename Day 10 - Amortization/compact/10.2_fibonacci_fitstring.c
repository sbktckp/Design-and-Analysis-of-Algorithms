/*
 * Day 10, Q10.2  Fibonacci fitstring, increment and decrement
 *
 * Idea: instead of bits standing for 1, 2, 4, 8, the digits stand for Fibonacci
 * numbers. A fit at position i means Fi is part of the sum, and fits start at
 * position 2 because F1 and F2 are both 1. So 101110 is F6+F4+F3+F2, which is
 * 8+3+2+1 = 14.
 *
 * The catch is that a number has many valid fitstrings, and that is exactly
 * what makes constant amortized time possible. Rather than forcing one canonical
 * form after every step, the array is allowed to hold a 2 for a moment and is
 * then repaired locally by three identities:
 *   a[i] = 2       becomes  F(i+1) + F(i-2)     because 2Fi = F(i+1) + F(i-2)
 *   a[i] = a[i+1] = 1 becomes F(i+2)             because Fi + F(i+1) = F(i+2)
 *   borrowing down  Fi = F(i-1) + F(i-2)
 *
 * Each repair is a fixed amount of work and each one lowers the count of set
 * fits and adjacent pairs, so a long chain of repairs has to have been paid for
 * by the cheap steps that built it up. That is the amortized argument.
 *
 * Increment is one line: add one to position 2, then repair. Decrement borrows
 * downwards until something worth 1 or 2 is available, takes one away, repairs.
 *
 * Input
 *   1 increment 2 decrement 3 exit: 1  (five times, then 2, then 3)
 *
 * Output
 *   value = 1 fitstring = 1
 *   value = 2 fitstring = 10
 *   value = 3 fitstring = 100
 *   value = 4 fitstring = 101
 *   value = 5 fitstring = 1000
 *   value = 4 fitstring = 101
 *
 *   Read 101 as F4 + F2, that is 3 + 1 = 4. Read 1000 as F5, that is 5.
 */
#include <stdio.h>
int a[90];
long long F[90];
void norm() {
    int c = 1, i;
    while (c) {
        c = 0;
        for (i = 2; i < 80; i++) {
            if (a[i] >= 2) {
                c = 1;
                if (i == 2) { a[2] -= 2; a[3]++; }
                else if (i == 3) { a[3] -= 2; a[4]++; a[2]++; }
                else { a[i] -= 2; a[i + 1]++; a[i - 2]++; }
            } else if (a[i] == 1 && a[i + 1] == 1) { c = 1; a[i] = 0; a[i + 1] = 0; a[i + 2]++; }
        }
    }
}
int low() { int i; for (i = 2; i < 80; i++) if (a[i]) return i; return -1; }
long long val() { int i; long long s = 0; for (i = 2; i < 80; i++) s += a[i] * F[i]; return s; }
void show() {
    int i, h = 2;
    for (i = 79; i >= 2; i--) if (a[i]) { h = i; break; }
    printf("value = %lld fitstring = ", val());
    for (i = h; i >= 2; i--) printf("%d", a[i]);
    printf("\n");
}
int main() {
    int i, op;
    F[1] = F[2] = 1;
    for (i = 3; i < 90; i++) F[i] = F[i - 1] + F[i - 2];
    for (;;) {
        printf("1 increment 2 decrement 3 exit: ");
        if (scanf("%d", &op) != 1 || op == 3) return 0;
        if (op == 1) { a[2]++; norm(); }
        else if (low() > 0) {
            while ((i = low()) > 3) { a[i]--; a[i - 1]++; a[i - 2]++; }
            if (low() == 2) a[2]--; else { a[3]--; a[2]++; }
            norm();
        }
        show();
    }
}

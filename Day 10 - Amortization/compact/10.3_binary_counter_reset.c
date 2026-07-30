/*
 * Day 10, Q10.3  Binary counter with INCREMENT and RESET
 *
 * Idea: incrementing a binary counter flips the run of trailing 1s to 0 and
 * then sets the next bit. Most increments are cheap, a few are expensive, and
 * on average it is about 2 flips, the classic amortized result.
 *
 * RESET is the interesting part. Clearing all 32 bits every time would cost 32
 * regardless, so a sequence of n resets would cost 32n. Keeping a pointer to
 * the highest 1 ever set means RESET only clears up to there, so it can never
 * cost more than what INCREMENT actually built up.
 *
 * The potential function makes it precise. Let PHI be the number of 1 bits plus
 * (high + 1).
 *   INCREMENT clears t trailing ones and sets one bit, real cost t+1, while PHI
 *   drops by t-1 and rises by at most 1, so the amortized cost is at most 3.
 *   RESET costs high+2 and drops PHI by at least high+1, so its amortized cost
 *   is at most 1.
 * Both constant, so n operations cost O(n) in total.
 *
 * Input
 *   1 increment 2 reset 3 exit:  1, 1, 2, 1, 2, then 3
 *
 * Output
 *   00000000 initial cost 0 total 0
 *   00000001 increment cost 1 total 1
 *   00000010 increment cost 2 total 3
 *   00000000 reset cost 3 total 6
 *   00000001 increment cost 1 total 7
 *   00000000 reset cost 2 total 9
 *
 *   Five operations, 9 units. The second increment costs 2 because it had to
 *   clear one trailing 1 before setting bit 1. The second reset costs less than
 *   the first because the counter had not climbed as high.
 */
#include <stdio.h>
int b[32], high = -1;
long total = 0;
void show(char *op, long c) {
    int i;
    for (i = 7; i >= 0; i--) printf("%d", b[i]);
    printf(" %s cost %ld total %ld\n", op, c, total);
}
int main() {
    int i, op;
    long c;
    show("initial", 0);
    for (;;) {
        printf("1 increment 2 reset 3 exit: ");
        if (scanf("%d", &op) != 1 || op == 3) return 0;
        c = 0;
        if (op == 1) {
            i = 0;
            while (b[i] == 1) { b[i] = 0; c++; i++; }
            b[i] = 1; c++;
            if (i > high) high = i;
            total += c;
            show("increment", c);
        } else {
            c = 1;
            for (i = 0; i <= high; i++) { b[i] = 0; c++; }
            high = -1; total += c;
            show("reset", c);
        }
    }
}

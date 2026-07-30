/*
 * Day 2, Q2.3  GCD of every pair by recursion, file to file
 *
 * Idea: Euclid's rule, gcd(a, b) = gcd(b, a mod b), with gcd(a, 0) = a as the
 * stopping case. Each step replaces the pair with a smaller pair, so it ends
 * quickly, in about log of the smaller number steps.
 *
 * Run it with no arguments and it uses the two files in ../data/. Or give it
 * both names, the way the sheet writes it:
 *   gcc 2.3_gcd_pairs.c -o lab2q2
 *   ./lab2q2 ../data/inGcd.dat ../data/outGcd.dat
 *
 * Input
 *   data/inGcd.dat holds pairs:  8 12  20 45  30 80  14 21  100 75 ...
 *
 * Output, written to outGcd.dat and echoed to the screen
 *   The GCD of 8 and 12 is 4
 *   The GCD of 20 and 45 is 5
 *   The GCD of 30 and 80 is 10
 *   The GCD of 14 and 21 is 7
 *   The GCD of 100 and 75 is 25
 */
#include <stdio.h>
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main(int argc, char *argv[]) {
    char *sf = argc > 1 ? argv[1] : "../data/inGcd.dat";
    char *df = argc > 2 ? argv[2] : "../data/outGcd.dat";
    int a, b, c;
    FILE *in = fopen(sf, "r"), *out = fopen(df, "w");
    if (!in || !out) { printf("Cannot open %s or %s\n", sf, df); return 1; }
    while (fscanf(in, "%d %d", &a, &b) == 2)
        fprintf(out, "The GCD of %d and %d is %d\n", a, b, gcd(a, b));
    fclose(in); fclose(out);
    out = fopen(df, "r");
    while ((c = fgetc(out)) != EOF) putchar(c);
    return 0;
}

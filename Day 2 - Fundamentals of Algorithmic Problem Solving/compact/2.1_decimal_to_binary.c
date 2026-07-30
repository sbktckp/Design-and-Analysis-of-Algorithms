/*
 * Day 2, Q2.1  Decimal to binary by recursion, file to file
 *
 * Idea: bin() calls itself on v/2 BEFORE printing v%2. The recursion therefore
 * reaches the highest bit first and prints on the way back out, so the digits
 * come in the right order with no reversing. The bits counter fixes the width
 * at 16, which is what pads 30 into 0000000000011110.
 *
 * Compile and run
 *   gcc 2.1_decimal_to_binary.c -o lab2q1
 *   ./lab2q1 3 ../data/inDec.dat ../data/outBin.dat
 *
 * Input
 *   data/inDec.dat holds:  30 75 2564 0 1 255 ...
 *   argv gives n = 3, the source name, the destination name
 *
 * Output, written to outBin.dat and echoed to the screen
 *   The binary equivalent of 30 is 0000000000011110
 *   The binary equivalent of 75 is 0000000001001011
 *   The binary equivalent of 2564 is 0000101000000100
 */
#include <stdio.h>
#include <stdlib.h>
void bin(int v, int bits, FILE *f) {
    if (bits == 0) return;
    bin(v / 2, bits - 1, f);
    fprintf(f, "%d", v % 2);
}
int main(int argc, char *argv[]) {
    FILE *in = fopen(argv[2], "r"), *out = fopen(argv[3], "w");
    int n = atoi(argv[1]), i, v;
    for (i = 0; i < n && fscanf(in, "%d", &v) == 1; i++) {
        fprintf(out, "The binary equivalent of %d is ", v);
        bin(v, 16, out);
        fprintf(out, "\n");
    }
    fclose(in); fclose(out);
    out = fopen(argv[3], "r");
    while ((i = fgetc(out)) != EOF) putchar(i);
    return 0;
}

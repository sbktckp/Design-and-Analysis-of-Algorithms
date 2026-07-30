/*
 * 2.1 Decimal to Binary
 *
 * Aim: convert the first 'n' decimal numbers of a disc file to binary using
 *      recursion, store the binary values in a separate disc file, then
 *      display the decimal numbers and their binary equivalents from that
 *      output file.
 *
 * Note: n, source file name and destination file name come from the command
 *       line arguments. Run with no arguments and it falls back to n = 15 and
 *       the two files in data/, so it always does something useful:
 *
 *          ./bin/2.1_decimal_to_binary
 *          ./bin/2.1_decimal_to_binary 150 data/inDec.dat data/outBin.dat
 *
 * Method: write_binary() recurses on value >> 1 before printing the current
 *         bit, so the most significant bit is emitted first and no reversal
 *         is needed. Fixed width of 16 bits matches the sample output.
 */
#include <stdio.h>
#include <stdlib.h>

#define BITS 16
#define MAX_VALUE 65535L

static void write_binary(unsigned value, int bits, FILE *out)
{
    if (bits == 0)
        return;
    write_binary(value >> 1, bits - 1, out);
    fputc('0' + (int)(value & 1u), out);
}

int main(int argc, char *argv[])
{
    const char *src_path = "data/inDec.dat";
    const char *dst_path = "data/outBin.dat";
    FILE *src, *dst;
    long n = 15, i, value;
    char line[256];

    if (argc == 4) {
        n = strtol(argv[1], NULL, 10);
        src_path = argv[2];
        dst_path = argv[3];
    } else if (argc != 1) {
        fprintf(stderr, "Usage: %s [<n> <source file> <destination file>]\n", argv[0]);
        fprintf(stderr, "With no arguments it reads %s and writes %s\n", src_path, dst_path);
        return 1;
    }

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    src = fopen(src_path, "r");
    if (src == NULL) {
        perror(src_path);
        fprintf(stderr, "Run this from inside the day folder, or use ./run 2.1\n");
        return 1;
    }
    dst = fopen(dst_path, "w");
    if (dst == NULL) {
        perror(dst_path);
        fclose(src);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(src, "%ld", &value) != 1)
            break;                      /* file holds fewer than n numbers */
        if (value < 0 || value > MAX_VALUE) {
            fprintf(stderr, "Skipping %ld, outside 0 to %ld\n", value, MAX_VALUE);
            continue;
        }
        fprintf(dst, "The binary equivalent of %ld is ", value);
        write_binary((unsigned)value, BITS, dst);
        fputc('\n', dst);
    }
    fclose(src);
    fclose(dst);

    dst = fopen(dst_path, "r");
    if (dst == NULL) {
        perror(dst_path);
        return 1;
    }
    printf("Contents of the output disc file \"%s\":\n", dst_path);
    while (fgets(line, sizeof line, dst) != NULL)
        fputs(line, stdout);
    fclose(dst);

    return 0;
}

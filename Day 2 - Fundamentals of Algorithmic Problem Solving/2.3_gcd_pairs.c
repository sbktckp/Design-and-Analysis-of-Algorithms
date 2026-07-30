/*
 * 2.3 GCD of Pairs
 *
 * Aim: find the GCD of two numbers using recursion. Read every pair of
 *      numbers from a file and store the results in a separate file.
 *
 * Note: source file name and destination file name come from the command line
 *       arguments. Run with no arguments and it falls back to the two files in
 *       data/, so it always does something useful:
 *
 *          ./bin/2.3_gcd_pairs
 *          ./bin/2.3_gcd_pairs data/inGcd.dat data/outGcd.dat
 *
 * Method: recursive Euclidean algorithm, gcd(a, b) = gcd(b, a mod b).
 *         Time O(log min(a, b)) per pair.
 */
#include <stdio.h>
#include <stdlib.h>

static long gcd(long a, long b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    const char *src_path = "data/inGcd.dat";
    const char *dst_path = "data/outGcd.dat";
    FILE *src, *dst;
    long a, b, pairs = 0;
    char line[256];

    if (argc == 3) {
        src_path = argv[1];
        dst_path = argv[2];
    } else if (argc != 1) {
        fprintf(stderr, "Usage: %s [<source file> <destination file>]\n", argv[0]);
        fprintf(stderr, "With no arguments it reads %s and writes %s\n", src_path, dst_path);
        return 1;
    }

    src = fopen(src_path, "r");
    if (src == NULL) {
        perror(src_path);
        fprintf(stderr, "Run this from inside the day folder, or use ./run 2.3\n");
        return 1;
    }
    dst = fopen(dst_path, "w");
    if (dst == NULL) {
        perror(dst_path);
        fclose(src);
        return 1;
    }

    while (fscanf(src, "%ld %ld", &a, &b) == 2) {
        long x = labs(a), y = labs(b);
        fprintf(dst, "The GCD of %ld and %ld is %ld\n", a, b, gcd(x, y));
        pairs++;
    }
    fclose(src);
    fclose(dst);

    if (pairs == 0) {
        fprintf(stderr, "No complete pairs found in %s\n", src_path);
        return 1;
    }

    dst = fopen(dst_path, "r");
    if (dst == NULL) {
        perror(dst_path);
        return 1;
    }
    printf("Contents of the output disc file \"%s\" (%ld pairs):\n", dst_path, pairs);
    while (fgets(line, sizeof line, dst) != NULL)
        fputs(line, stdout);
    fclose(dst);

    return 0;
}

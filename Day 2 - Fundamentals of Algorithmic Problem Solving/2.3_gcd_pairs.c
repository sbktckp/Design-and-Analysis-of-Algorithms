/*
 * 2.3 GCD of Pairs
 *
 * Aim: find the GCD of two numbers using recursion. Read every pair of
 *      numbers from a file and store the results in a separate file.
 *
 * Note: source file name and destination file name come from the command
 *       line arguments. The source file holds at least 20 pairs.
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
    FILE *src, *dst;
    long a, b, pairs = 0;
    char line[256];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    src = fopen(argv[1], "r");
    if (src == NULL) {
        perror(argv[1]);
        return 1;
    }
    dst = fopen(argv[2], "w");
    if (dst == NULL) {
        perror(argv[2]);
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
        fprintf(stderr, "No complete pairs found in %s\n", argv[1]);
        return 1;
    }

    dst = fopen(argv[2], "r");
    if (dst == NULL) {
        perror(argv[2]);
        return 1;
    }
    printf("Contents of the output disc file \"%s\" (%ld pairs):\n", argv[2], pairs);
    while (fgets(line, sizeof line, dst) != NULL)
        fputs(line, stdout);
    fclose(dst);

    return 0;
}

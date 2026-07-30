/*
 * 1.2 Uppercase Convert
 *
 * Aim: convert the contents of a file to upper case and write the result to an
 *      output file.
 *
 * Method: copy character by character through toupper. The source is opened
 *         for reading and the destination is a DIFFERENT file, because opening
 *         the same name for writing truncates it to nothing before a single
 *         character can be read.
 *         Time O(n), space O(1).
 */
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *in_path = (argc > 1) ? argv[1] : "data/test.txt";
    const char *out_path = (argc > 2) ? argv[2] : "data/upper.txt";
    FILE *fp1, *fp2;
    int c;
    long copied = 0;

    fp1 = fopen(in_path, "r");
    if (fp1 == NULL) {
        printf("Cannot open %s for reading\n", in_path);
        return 1;
    }
    fp2 = fopen(out_path, "w");
    if (fp2 == NULL) {
        printf("Not able to open %s for writing\n", out_path);
        fclose(fp1);
        return 1;
    }

    /* Test for EOF BEFORE writing, or the EOF marker lands in the output. */
    while ((c = getc(fp1)) != EOF) {
        putc(toupper(c), fp2);
        copied++;
    }
    fclose(fp1);
    fclose(fp2);

    printf("%ld characters converted from %s into %s\n", copied, in_path, out_path);

    fp2 = fopen(out_path, "r");
    if (fp2 == NULL) {
        printf("Cannot reopen %s to display it\n", out_path);
        return 1;
    }
    printf("\nContents of %s:\n", out_path);
    while ((c = getc(fp2)) != EOF)
        putchar(c);
    fclose(fp2);

    return 0;
}

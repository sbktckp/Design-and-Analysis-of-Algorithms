/*
 * 1.1 Compare Files
 *
 * Aim: compare two files and report whether they are identical.
 *
 * Method: read both files one character at a time and stop at the first
 *         difference. Two files are identical only when every character
 *         matches AND both reach end of file together, so a file that is a
 *         prefix of the other is correctly reported as different.
 *         Time O(n), space O(1).
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp1, *fp2;
    char fname1[128], fname2[128];
    int ch1, ch2;
    long position = 0;
    int identical = 1;

    printf("Enter name of first file: ");
    if (scanf("%127s", fname1) != 1)
        return 1;
    printf("Enter name of second file: ");
    if (scanf("%127s", fname2) != 1)
        return 1;

    fp1 = fopen(fname1, "rb");
    if (fp1 == NULL) {
        printf("Cannot open %s for reading\n", fname1);
        return 1;
    }
    fp2 = fopen(fname2, "rb");
    if (fp2 == NULL) {
        printf("Cannot open %s for reading\n", fname2);
        fclose(fp1);
        return 1;
    }

    for (;;) {
        ch1 = getc(fp1);
        ch2 = getc(fp2);

        if (ch1 != ch2) {
            identical = 0;
            break;
        }
        if (ch1 == EOF)                 /* both ended at the same place */
            break;
        position++;
    }

    fclose(fp1);
    fclose(fp2);

    if (identical) {
        printf("Files are identical\n");
    } else {
        printf("Files are not identical\n");
        if (ch1 == EOF)
            printf("%s ends after %ld characters, %s continues\n",
                   fname1, position, fname2);
        else if (ch2 == EOF)
            printf("%s ends after %ld characters, %s continues\n",
                   fname2, position, fname1);
        else
            printf("First difference at character %ld: '%c' against '%c'\n",
                   position + 1, ch1, ch2);
    }
    return 0;
}

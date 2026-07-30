/*
 * 1.3 Odd Even Split
 *
 * Aim: read numbers from the user and write them to a file, then read that
 *      file back and store the numbers in two separate files, one for odd and
 *      one for even.
 *
 * Files, all under data/
 *      DATA  every number the user typed
 *      ODD   the odd ones
 *      EVEN  the even ones
 *
 * Entry stops at -1 or after MAX_COUNT numbers.
 *
 * Method: three passes, one to capture input, one to split, one to display.
 *         The split reads DATA rather than the array in memory, which is what
 *         the question asks for. Time O(n), space O(1).
 *
 * The remainder is compared with != 0 rather than == 0 so that negative odd
 * numbers, where n % 2 is -1 in C, are still classified as odd.
 */
#include <stdio.h>

#define MAX_COUNT 30

static void show_file(const char *label, const char *path)
{
    FILE *fp = fopen(path, "r");
    int number;

    printf("\n%s\n", label);
    if (fp == NULL) {
        perror(path);
        return;
    }
    while (fscanf(fp, "%d", &number) == 1)
        printf("%4d", number);
    putchar('\n');
    fclose(fp);
}

int main(void)
{
    FILE *f1, *f2, *f3;
    int number, i, count = 0, odd = 0, even = 0;

    f1 = fopen("data/DATA.dat", "w");
    if (f1 == NULL) {
        perror("data/DATA.dat");
        return 1;
    }

    printf("Enter up to %d numbers, -1 to stop:\n", MAX_COUNT);
    for (i = 0; i < MAX_COUNT; i++) {
        if (scanf("%d", &number) != 1)
            break;
        if (number == -1)
            break;
        fprintf(f1, "%d\n", number);
        count++;
    }
    fclose(f1);
    printf("%d numbers written to data/DATA.dat\n", count);

    f1 = fopen("data/DATA.dat", "r");
    f2 = fopen("data/ODD.dat", "w");
    f3 = fopen("data/EVEN.dat", "w");
    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        perror("opening the data files");
        if (f1 != NULL)
            fclose(f1);
        if (f2 != NULL)
            fclose(f2);
        if (f3 != NULL)
            fclose(f3);
        return 1;
    }

    while (fscanf(f1, "%d", &number) == 1) {
        if (number % 2 != 0) {
            fprintf(f2, "%d\n", number);
            odd++;
        } else {
            fprintf(f3, "%d\n", number);
            even++;
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);

    show_file("Contents of DATA file:", "data/DATA.dat");
    show_file("Contents of ODD file:", "data/ODD.dat");
    show_file("Contents of EVEN file:", "data/EVEN.dat");
    printf("\n%d odd, %d even, %d in total\n", odd, even, count);

    return 0;
}

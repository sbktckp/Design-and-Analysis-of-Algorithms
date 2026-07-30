/*
 * Assignment 1, Q1.3  Split numbers into odd and even files
 *
 * Idea: three short passes. Write everything the user types into DATA.dat.
 * Reopen it for reading and send each number to ODD.dat or EVEN.dat. Reopen
 * those two and print them. The split reads the file rather than an array in
 * memory, which is what the question asks for.
 *
 * The neat line is fprintf(x % 2 ? f2 : f3, ...). In C any non zero value is
 * true, so x % 2 picks the odd file for odd numbers with no comparison at all.
 * It also handles negatives correctly, since -7 % 2 is -1, which is still true.
 * Writing x % 2 == 1 instead would quietly file negative odd numbers as even.
 *
 * Input
 *   Enter numbers, -1 to stop: 10 7 4 25 30 13 -1
 *
 * Output
 *   ODD: 7 25 13
 *   EVEN: 10 4 30
 *
 *   data/DATA.dat now holds all six numbers, ODD.dat holds three, EVEN.dat
 *   holds three.
 */
#include <stdio.h>
int main() {
    FILE *f1 = fopen("../data/DATA.dat", "w"), *f2, *f3;
    int x;
    printf("Enter numbers, -1 to stop: ");
    while (scanf("%d", &x) == 1 && x != -1) fprintf(f1, "%d ", x);
    fclose(f1);
    f1 = fopen("../data/DATA.dat", "r");
    f2 = fopen("../data/ODD.dat", "w");
    f3 = fopen("../data/EVEN.dat", "w");
    while (fscanf(f1, "%d", &x) == 1) fprintf(x % 2 ? f2 : f3, "%d ", x);
    fclose(f1); fclose(f2); fclose(f3);
    f2 = fopen("../data/ODD.dat", "r");
    printf("ODD: ");
    while (fscanf(f2, "%d", &x) == 1) printf("%d ", x);
    f3 = fopen("../data/EVEN.dat", "r");
    printf("\nEVEN: ");
    while (fscanf(f3, "%d", &x) == 1) printf("%d ", x);
    printf("\n");
    return 0;
}

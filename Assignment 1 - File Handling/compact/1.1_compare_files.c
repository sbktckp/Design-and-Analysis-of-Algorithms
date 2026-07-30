/*
 * Assignment 1, Q1.1  Are two files identical
 *
 * Idea: read both files one character at a time in step. Stop the moment the
 * two characters differ, or when both hit end of file together. If the loop
 * ended because c1 equals c2, the files matched all the way to EOF and are
 * identical.
 *
 * Two details that matter. The characters are read into int, not char, because
 * EOF is not a character value and would be indistinguishable otherwise. And
 * both files must end at the same moment: if one is a prefix of the other, one
 * getc returns a real character while the other returns EOF, they differ, and
 * the files are correctly reported as different.
 *
 * Input
 *   First file: ../data/first.txt
 *   Second file: ../data/second.txt
 *
 * Output
 *   Files are identical
 *
 *   Trying ../data/first.txt against ../data/third.txt prints
 *   Files are not identical
 */
#include <stdio.h>
int main() {
    FILE *f1, *f2;
    char n1[50], n2[50];
    int c1, c2;
    printf("First file: "); scanf("%49s", n1);
    printf("Second file: "); scanf("%49s", n2);
    f1 = fopen(n1, "r"); f2 = fopen(n2, "r");
    do {
        c1 = getc(f1); c2 = getc(f2);
    } while (c1 == c2 && c1 != EOF);
    fclose(f1); fclose(f2);
    printf(c1 == c2 ? "Files are identical\n" : "Files are not identical\n");
    return 0;
}

/*
 * Assignment 1, Q1.2  Convert a file to upper case
 *
 * Idea: copy the file one character at a time, passing each through toupper,
 * which leaves digits and punctuation alone and only lifts lowercase letters.
 *
 * The mistake to avoid here is opening the same file for reading and for
 * writing. Mode "w" empties the file the instant it opens, so reading from the
 * same name afterwards finds nothing. Read from test.txt, write to upper.txt.
 *
 * The second thing to get right is testing for EOF before writing. A do while
 * loop that converts and writes first will append one junk character, because
 * EOF is a signal, not a character.
 *
 * Input
 *   data/test.txt holds:
 *   Hello World from the DAA lab.
 *   File handling in c is mostly getc and putc.
 *
 * Output, written to data/upper.txt and echoed to the screen
 *   HELLO WORLD FROM THE DAA LAB.
 *   FILE HANDLING IN C IS MOSTLY GETC AND PUTC.
 */
#include <stdio.h>
#include <ctype.h>
int main() {
    FILE *f1 = fopen("../data/test.txt", "r"), *f2 = fopen("../data/upper.txt", "w");
    int c;
    while ((c = getc(f1)) != EOF) putc(toupper(c), f2);
    fclose(f1); fclose(f2);
    f2 = fopen("../data/upper.txt", "r");
    while ((c = getc(f2)) != EOF) putchar(c);
    return 0;
}

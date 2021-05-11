/* Ex.1-9:
 * Write a program to copy it's input to it's output, 
 * replacing each string of one or more blanks by a single blank.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    int c;
    int wasBlank = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (wasBlank == 0) {
                printf("%c", c);
                wasBlank = 1;
            }
        }
        if (c != ' ') {
            printf("%c", c);
            wasBlank = 0;
        }
    }
}

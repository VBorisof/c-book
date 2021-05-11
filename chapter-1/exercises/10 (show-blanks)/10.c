/* Ex.1-10
 * Write a Program to copy its input to its output,
 * -------------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            printf("\\t");
        }
        if (c == '\b') {
            printf("\\b");
        }
        if (c == '\\') {
            printf("\\\\");
        }
        if (c != '\t') {
            if (c != '\b') {
                if (c != '\\') {
                    printf("%c", c);
                }
            }
        }
    }
}

#include <stdio.h>

int main() {
    int c;
    long nl = 0, nb = 0, nt = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++nl;
        }
        if (c == '\t') {
            ++nt;
        }
        if (c == ' ') {
            ++nb;
        }
    }
    printf("You have entered %d lines my dude. %d tabs and %d blanks too.\n", nl, nt, nb);
}

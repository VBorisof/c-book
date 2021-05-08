#include <stdio.h>

int main() {
    int c;
    long nc;
    nc = 0;

    while ((c = getchar()) != EOF) {
        if (c != 10) ++nc;
    }
    printf("You entered %ld characters my dude.\n", nc);
}

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

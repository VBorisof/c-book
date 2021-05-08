#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
    int c;
    int state = OUT;       

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state != OUT) printf("\n");
            state = OUT;
        }
        else {
            state = IN;
            printf("%c", c);
        }
    }
}

#include <stdio.h> 

#define IN  1 // INside a word
#define OUT 0 // OUTside a word

int main() {
    int c, nl, nw, nc, state;

    state = OUT;

    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        }
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }

    printf("l:%d w:%d c:%d\n", nl, nw, nc);
}


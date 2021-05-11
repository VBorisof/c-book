/* Ex.1-13
 * Write a program to print a histogram of the lengths of words in its input. 
 * It is easy to draw the histogram with the bars horizontal.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define MAX_WORDS 1000

#define IN  1
#define OUT 0

int main() {
    int c, state;
    state = OUT;
    
    int wordSizes [MAX_WORDS];
    int wordIndex = 0;

    for (int i = 0; i < MAX_WORDS; ++i) {
        wordSizes[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t' || c == '.' || c == ',') {
            if (state != OUT) {
                ++wordIndex;
            }
            state = OUT;
        }
        else {
            state = IN;
            ++wordSizes[wordIndex];
        }
    }

    int maxHeight = -1;
    for (int i = 0; i < wordIndex; ++i) {
        if (wordSizes[i] > maxHeight) {
            maxHeight = wordSizes[i];
        }
    }

    for (int row = maxHeight; row >= 0; --row) {
        for (int i = 0; i <= wordIndex; ++i) {
            if (wordSizes[i] > row) {
                printf("┃");
            }
            else printf(" ");
        }
        printf("\n");
    }
    
    for (int i = 0; i <= wordIndex; ++i) {
        printf("-");
    }
    printf("\n");
}


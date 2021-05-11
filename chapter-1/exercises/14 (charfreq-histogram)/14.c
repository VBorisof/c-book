/* Ex.1-14
 * Write a program to print a histogram of the frequencies of 
 * different characters in its input.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define DIGIT_OFFSET  48
#define UPCASE_OFFSET 65
#define LOCASE_OFFSET 97

#define NUM_DIGITS    10
#define NUM_LETTERS   26
#define NUM_CHARS     62

int main() {
    int charFrequencies[NUM_CHARS]; 
    for (int i = 0; i < NUM_CHARS; ++i) {
        charFrequencies[i] = 0;
    }

    int c;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            ++charFrequencies[c - DIGIT_OFFSET];
        }
        if (c >= 'A' && c <= 'Z') {
            ++charFrequencies[NUM_DIGITS + c - UPCASE_OFFSET];
        }
        if (c >= 'a' && c <= 'z') {
            ++charFrequencies[NUM_LETTERS + NUM_DIGITS + c - LOCASE_OFFSET];
        }
    }

    int maxHeight = -1;
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (charFrequencies[i] > maxHeight) {
            maxHeight = charFrequencies[i];
        }
    }

    for (int row = maxHeight; row >= 0; --row) {
        for (int i = 0; i < NUM_CHARS; ++i) {
            if (charFrequencies[i] > row) {
                printf("┃");
            }
            else printf(" ");
        }
        printf("\n");
    }
    
    for (int i = 0; i < NUM_CHARS; ++i) {
        printf("-");
    }
    printf("\n");
    
    for (int i = DIGIT_OFFSET; i < DIGIT_OFFSET+NUM_DIGITS; ++i) {
        printf("%c", i);
    }

    for (int i = UPCASE_OFFSET; i < UPCASE_OFFSET+NUM_LETTERS; ++i) {
        printf("%c", i);
    }

    for (int i = LOCASE_OFFSET; i < LOCASE_OFFSET+NUM_LETTERS; ++i) {
        printf("%c", i);
    }

    printf("\n");
}


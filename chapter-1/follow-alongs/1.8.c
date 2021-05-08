#include <stdio.h>

/*
    Raise base to the nth power, for n >= 0
*/
int power(int base, int n) {
    int p;
    for (p = 1; n > 0; --n) {
        p = p*base;
    }
    return p;
}

int main() {
    printf("┎─────┰───────┰───────┒\n");
    printf("┃ %3s ┃ %5s ┃ %5s ┃\n", "i", "2^i", "3^i");
    printf("┠─────╂───────╂───────┨\n");
    for (int i = 0; i < 4; ++i) {
        printf(
           "┃ %3d ┃ %5d ┃ %5d ┃\n", 
           i, power(2, i), power(3, i));
    }
    printf("┖─────┸───────┸───────┚\n");
    return 0;
}

#include <stdio.h>
 
int power(int m, int n);
int power(int base, int n) {
    int i, p;
    p = 1;
    for (i = 1; i <= n; ++i) {
        p = p * base;
    }
    return p;
}

int main() {
    printf("┎─────┰───────┰───────┒\n");
    printf("┃ %3s ┃ %5s ┃ %5s ┃\n", "i", "2^i", "3^i");
    printf("┠─────╂───────╂───────┨\n");
    for (int i = 0; i < 4; ++i) {
        printf("┃ %3d ┃ %5d ┃ %5d ┃\n", i, power(2, i), power(3, i));
    }
    printf("┖─────┸───────┸───────┚\n");
    return 0;
}

#include <stdio.h>

int c;

int read() {
    c = getchar();
    int result = (c != EOF);
    printf("[D] predecate is %2i\n", result);
    return result;
}

int main() {
    while (read()) {
        printf("%d -- %c\n", c, c);
    }
}

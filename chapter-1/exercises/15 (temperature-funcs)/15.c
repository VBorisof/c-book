#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP  20

float toFahr(int celsius) {
    return (9.0/5.0)*celsius + 32;
}

int main() {
    printf("-------------\n");
    printf("|%4s|%5s |\n", "CELS", "FAHR");
    printf("-----+-------\n");
    
    for (int celsius = LOWER; celsius <= UPPER; celsius += STEP) {
        printf("|%3d | %5.1f|\n", celsius, toFahr(celsius));
    }
    printf("-------------\n");
}

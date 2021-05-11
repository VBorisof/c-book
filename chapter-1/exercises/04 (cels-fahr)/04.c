/* Ex. 1-4:
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define LOWER 0
#define UPPER 520
#define STEP  20

int main() {
    printf("-------------\n");
    printf("|%4s|%5s |\n", "CELS", "FAHR");
    printf("-----+-------\n");
    
    for (int celsius = UPPER; celsius >= LOWER; celsius -= STEP) {
        printf("|%3d | %5.1f|\n", celsius, (9.0/5.0)*celsius + 32);
    }
    printf("-------------\n");
}



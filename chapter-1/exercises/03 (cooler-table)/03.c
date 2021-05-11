/* Ex. 1-3.
 * Modify the temperature conversion program to print a heading above the table 
 * -------------------------------------------------------------------------- */

#include <stdio.h>

main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("-------------\n");
    printf("|%4s|%5s |\n", "FAHR", "CELS");
    printf("-----+-------\n");
    while (fahr <= upper) {
        celsius = (5.0f/9.0f) * (fahr-32);
        printf("|%3.0f | %5.1f|\n", fahr, celsius);
        fahr = fahr + step;
    }
    printf("-------------\n");
}

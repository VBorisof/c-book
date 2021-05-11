/* Ex.1-20
 * Write a program detab that replaces tabs in the input with the proper 
 * number of blanks to space to the next tab stop. Assume a fixed set of tab 
 * stops, say every n columns. Should n be a variable or a symbolic parameter?
 * -------------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    int tabcols = 4; /* How long are tabs? TODO: Read from args. */
    
    int tabstopcounter, spacecounter;
    tabstopcounter = spacecounter = 0;

    char c;
    while ((c=getchar()) != EOF) {
        if (c == '\t') {
            /* We want to replace this tab by some amount of spaces.
             * Has to be based on tabstops. So, keep track of the
             * `tabstopcounter`, increase it whenever we insert
             * a non-tab character, and set it to 0 every time it reaches
             * `tabcols` or after we encounter a tab, or if we start a new line.
             * */ 
            spacecounter += tabcols-tabstopcounter;
            tabstopcounter = 0;

            /* Insert all the spaces... */
            while (spacecounter > 0) {
                putchar(' ');
                --spacecounter;
            }
        }
        else {
            /* If we encounter a regular char, just print it. */
            putchar(c);
            
            /* Drop the counter if we start a new line or if we hit tabcols. */
            if (c == '\n' || ++tabstopcounter >= tabcols) {
                tabstopcounter = 0;
            }
        }
    }
    return 0;
}

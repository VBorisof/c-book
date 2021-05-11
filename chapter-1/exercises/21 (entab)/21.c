/* Ex.1-21
 * Write a program entab that replaces strings of blanks by the minimum 
 * number of tabs and blanks to achieve the same spacing. 
 * Use the same tab stops as for detab. 
 * When either a tab or a single blank would suffice to reach a tab stop, 
 * which should be given preference?
 * -------------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    int tabcols = 4;

    int tabstopcounter = 0; /* Counts global tab stops.      */
    int spacecounter   = 0; /* Counts if we have any spaces. */
    char c;

    /* Main loop, read chars while we have enough space */
    while ((c=getchar()) != EOF) {
        /* Reset `tabstopcounter` if needed */
        if (tabstopcounter >= tabcols) {
            tabstopcounter = 0;
        }
        
        /* We will just count spaces and insert tabs straight away. */
        if (c == ' ' || c == '\t') {
            /* If spacecounter and tabstopcounter are at tabcols,
             * it's time to place a tab. 
             * Same is true if we actually need a tab, of course.
             * */
            if (c == '\t' || ++spacecounter+tabstopcounter == tabcols) {
                putchar('\t');
                tabstopcounter = 0;
                spacecounter = 0;
            }
        }
        /* If we get a line break, break the line and reset counters. */
        else if (c == '\n') {
            putchar('\n');
            tabstopcounter = 0;
            spacecounter = 0;
        }
        /* If we get any other char... */
        else {
            /* See if we have any spaces we have to put first... */
            while (spacecounter > 0) {
                putchar(' ');
                ++tabstopcounter;
                --spacecounter;
            }

            /* Then just place the character */
            putchar(c);
            ++tabstopcounter;
        }
    }
    
    return 0;
}

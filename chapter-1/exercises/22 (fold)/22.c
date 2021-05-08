#include <stdio.h>

int main() {
    int foldcol, tabcols, charcounter, tabstopcounter;
    charcounter = tabstopcounter = 0;

    tabcols = 4; /* How long are the tabs? TODO: Read from args. */
    foldcol = 5; /* At which column to fold? TODO: Read from args. */
   
    if (foldcol <= tabcols) {
        fprintf(
            stderr, 
            "[!] Folding column is at or less than tab length. "
            "Tabs will be placed anyway.\n"
        );

    }

    char c;
    while ((c=getchar()) != EOF) {
        if (c == '\t') {
            /* Increase the charcounter by amount of 
             * spaces that we will put, and see if we need a newline. */
            charcounter += tabcols - tabstopcounter;
            if (charcounter >= foldcol - 1) {
                putchar('\n');
                charcounter = tabcols; /* 0 + tabcols */
            }
            putchar('\t');
            tabstopcounter = 0;
        }
        else {
            ++charcounter;
            /* If we have a newline or we are over the line, */
            if (c == '\n' || charcounter >= foldcol) {
                /* Place a newline and drop the charcounter. */
                putchar('\n');

                /* See if we will place exactly 1 character on the line.
                 * (we should if character is not newline.) */
                charcounter = c != '\n';

                tabstopcounter = 0;
            }

            if (c != '\n') {
                /* Place the non-newline character we have. */
                putchar(c);
                ++tabstopcounter;
            }
        }

        /* Reset the tabstopcounter if needed. */
        if (tabstopcounter >= tabcols) {
            tabstopcounter = 0;
        }
    }

    return 0;
}

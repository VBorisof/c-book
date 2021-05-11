/* Ex.1-22
 * Write a program to fold long input lines into two or more shorter lines 
 * after the last non-blank character that occurs before the n-th column 
 * of input. Make sure your program does something ntelligent with 
 * very long lines, and if there are no blanks or tabs 
 * before the specified column.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

/* Returned if cannot buffer properly due to length.   */
#define ERROR_BUFFER_TOO_SMALL  -1 

/* Returned if folding column is too close to tab len (<TABCOLS)*/
#define ERROR_FOLDCOL_TOO_SMALL -2

#define MAXBUFFER  2  /* How big is the buffer? */
#define TABCOLS    4  /* Tab length */
#define MAXCOLS    5  /* Maximum columns. Here, wrapping column. */


/* Keeping some stuff global, to reuse across function
 * calls, due to some edge cases related to very small buffers. 
 * */

/* Keep track of chars. Break when over MAXCOLS. */
int charcounter = 0;     
/* Keep track of tabs -> see how many spaces they represent on a given pos. */
int tabstopcounter = 0;     
/* Sometimes a buffer can overflow, but we still need a tab -> flag for that. */
int ispendingtab = FALSE; 
/* Same here, a buffer could overflow, but we need a new line. */
int ispendingnewline = FALSE;
/* Same here, a buffer could overflow, but we still need some character. */
int bufferchar = -1;

/* Read from standard input into the given buffer of given length, but add new
 * lines before the supplied foldcol, effectively folding all the input.
 * 
 * Errors:
 *  - ERROR_BUFFER_TOO_SMALL  (-1) - Cannot handle buffers of length<2.
 *  - ERROR_FOLDCOL_TOO_SMALL (-2) - Cannot handle foldcol<TABCOLS. 
 *
 * */
int fold(char buffer[], int length, int foldcol) {
    if (length < 2) {
        fprintf(stderr, "Sorry, buffers of length<2 are not supported.\n");
        return ERROR_BUFFER_TOO_SMALL;
    }
    if (foldcol <= TABCOLS) {
        fprintf(
            stderr, 
            "Sorry, cannot fold at column<=TABCOLS (%i).\n", TABCOLS
        );
        return ERROR_FOLDCOL_TOO_SMALL;
    }
    
    int i, c;
    i = 0;

    /* See if we have a tab from last time.
     * This could happen in case of buffer overflow.
     * */
    if (ispendingtab) {
        buffer[i] = '\t';
        ++i;
        ispendingtab = FALSE;
    }

    /* See if we need a new line from last time. */
    if (i < length-1 && ispendingnewline) {
        buffer[i] = '\n';
        ++i;
        charcounter = 0;
        tabstopcounter = 0;
        ispendingnewline = FALSE;
    }

    /* See if we have some character that needs
     * to be put from last time.
     * */
    if (i < length-1 && bufferchar > 0) {
        buffer[i] = bufferchar;
        ++i;
        ++charcounter;
        bufferchar = -1;
    }

    while (i < length-1 && (c=getchar()) != EOF) {
        /* See if we need a tab. */
        if (c == '\t') {
            /* Calculate the amount of space a tab would take... */
            charcounter += TABCOLS-tabstopcounter;
            if (charcounter >= foldcol-1) {
                buffer[i] = '\n';
                ++i;

                /* Insert a tab if we still can. */
                if (i < length-1) {
                    buffer[i] = '\t';
                    ++i;
                }
                /* Otherwise flag that we need a tab. */
                else ispendingtab = TRUE;

                /* Either way, we are on a new 
                 * line, and with a tab: */
                charcounter = TABCOLS;
            }
            else {
                /* We have line space, so just place a tab. */
                buffer[i] = '\t';
                ++i;
            }
            tabstopcounter = 0;
        }
       
        /* See if we need a new line. */ 
        if (c == '\n' || charcounter >= foldcol-1) {
            /* Check for overflow and raise a flag if needed. */

            if (i < length-1) {
                buffer[i] = '\n';
                ++i;
                charcounter = 0;
                tabstopcounter = 0;
            }
            else {
                ispendingnewline = TRUE;
            }
        }
        
        /* See if it's any other character. */
        if (c != '\n' && c != '\t') {
            /* Check for overflow and cache the char if needed. */

            if (i < length-1) {
                buffer[i] = c;
                ++i;
                ++charcounter;
            }
            else {
                bufferchar = c;
            }

            if (++tabstopcounter >= TABCOLS) {
                tabstopcounter = 0;
            }
        }
    }

    /* Terminate the string. */
    buffer[i] = '\0';

    /* Return the length of the string. */
    return i;
}

int main() {
    char buffer[MAXBUFFER];

    int result;
    while ((result=fold(buffer, MAXBUFFER, MAXCOLS)) > 0) {
        printf("%s", buffer);
    }

    return result;
}

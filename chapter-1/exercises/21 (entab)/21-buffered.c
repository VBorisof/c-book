/* Ex.1-21
 * Write a program entab that replaces strings of blanks by the minimum 
 * number of tabs and blanks to achieve the same spacing. 
 * Use the same tab stops as for detab. 
 * When either a tab or a single blank would suffice to reach a tab stop, 
 * which should be given preference?
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define MAXBUFFER 2 /* Defines the buffer sizes. */
#define TABCOLS   4 /* How wide are the tabs?    */

/*
 * Unfortunately forced to keep some things global, 
 * mostly to handle the bufferss longer than MAXBUFFER.
 * */

int  tabstopcounter =  0; /* Counts global tab stops.      */
int  spacecounter   =  0; /* Counts if we have any spaces. */
char bufferchar     = -1; /* Used for the space overflow.  */

/* Reads chars from standard output into a given buffer of given length,
 * while replacing as many spaces as it can with tabs.
 * Returns the length of the resulting string or an error code.
 * */
int entab(char buffer[], int length) {
    /* Unfortunately we can't currently handle buffers of size 1. :(
     * Don't think this is possible either, since we need at least 2 characters:
     * one for what we got from getchar(), and the other is for \0. */
    if (length < 2) {
        fprintf(stderr, "[!] Sorry, buffers of length<2 are not supported!\n");
        return -1;
    }

    int i, c;
    i = 0;

    /* First, see if we have any outstanding space to put, from the
     * last call to this function. It can happen that the buffer
     * overflowed last time (See (1) below). */
    while (i < length-1 && spacecounter > 0) {
        buffer[i] = ' ';
        ++i;
        ++tabstopcounter;
        --spacecounter;
    }

    /* Dump the buffer character if needed (See (1) below). */
    if (i < length-1 && bufferchar > 0) {
        buffer[i] = bufferchar;
        ++i;
        ++tabstopcounter;
        bufferchar = -1;
    }

    /* Main loop, read chars while we have enough space */
    while (i < length-1 && (c=getchar()) != EOF) {
        /* Reset `tabstopcounter` if needed */
        if (tabstopcounter >= TABCOLS) {
            tabstopcounter = 0;
        }
        
        /* We will just count spaces and insert tabs straight away. */
        if (c == ' ' || c == '\t') {
            /* If spacecounter and tabstopcounter are at TABCOLS,
             * it's time to place a tab. 
             * Same is true if we actually need a tab, of course.
             * */
            if (c == '\t' || ++spacecounter+tabstopcounter == TABCOLS) {
                buffer[i] = '\t';
                ++i;
                tabstopcounter = 0;
                spacecounter = 0;
            }
        }
        /* If we get a line break, break the line and reset counters. */
        else if (c == '\n') {
            buffer[i] = '\n';
            ++i;
            tabstopcounter = 0;
            spacecounter = 0;
        }
        /* If we get any other char... */
        else {
            /* See if we have any spaces we have to put first... */
            while (i < length-1 && spacecounter > 0) {
                buffer[i] = ' ';
                ++i;
                ++tabstopcounter;
                --spacecounter;
            }

            /* (1) It can happen that we still have spaces to put, but we also have
             * the next character to put. This means that the buffer has overflown,
             * and we should store the character for the next call to this function. 
             * */
            if (spacecounter > 0) {
                bufferchar = c;
            }
            /* Otherwise, all okay, just enplace the character. */
            else {
                buffer[i] = c;
                ++i;
                ++tabstopcounter;
            }
        }
    }
    
    /* Don't forget to terminate the string! */
    buffer[i] = '\0';


    /* Return the length. */
    return i;
}

int main() {
    char buffer[MAXBUFFER];

    while(entab(buffer, MAXBUFFER) > 0) {
        printf("%s", buffer);
    }
    
    return 0;
}

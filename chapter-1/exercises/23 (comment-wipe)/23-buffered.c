/* Ex.1-23
 * Write a program to remove all comments from a C program. 
 * Don’t forget to handle quoted strings and character constants properly. 
 * C comments don’t nest.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define FALSE 0
#define TRUE  1

#define MAXBUFFER 2 /* How long is the buffer? */

#define STATE_OUT           0 /* Normal, just put chars in. */ 
#define STATE_IN_COMMENT    1 /* Not going to write anything. */
#define STATE_IN_STRING     2 /* In string. Should still write. */
#define STATE_IN_CHAR       3 /* In char. Should still write. */
#define STATE_BEGIN_COMMENT 4 /* Might be a comment. Can still write. */
#define STATE_END_COMMENT   5 /* Might be a comment end. Can still not right. */

/* Keeping some stuff global again, to handle all-size buffers... */
int state = STATE_OUT; /* Keep track of text state. */

char bufferchar = -1;  /* Buffer might've overflown. 
                          Keep a char here for next time then.*/

/* Read from standard input into a buffer of specified length, and assume
 * the input is a C program, and remove all C comments. 
 * Only removes the comments, keeps the lines.
 * Only removes the /(*)...*(/) style comments.
 * */
int stripcomments(char buffer[], int length) {
    if (length < 2) {
        fprintf(stderr, "Sorry, buffer length<2 is not supported.");
    }

    int skipflag; /* If set, will not put a character. */ 
    int i, c;
    i = 0;

    /* Buffer might have overflown, place a 
     * character from last call if needed. */
    if (bufferchar > 0) {
        buffer[i] = bufferchar;
        ++i;
        bufferchar = -1;
    }

    while (i < length-1 && (c=getchar()) != EOF) {
        skipflag = FALSE;

        if (state == STATE_OUT) {
            if (c == '/') {
                /* We might be beginning a comment. 
                 * Set state to listen to this. */
                state = STATE_BEGIN_COMMENT;
            }

            /* If we encounter quotes, we entered into string/char. */
            if (c == '"' ) {
                state = STATE_IN_STRING;
            }
            if (c == '\'') {
                state = STATE_IN_CHAR;
            }
        }
        else if (state == STATE_BEGIN_COMMENT) {
            /* See if it's indeed a comment. */
            if (c == '*') {
                state = STATE_IN_COMMENT;
            }
            else {
                /* Not a comment afterall. Correct the mistake
                 * of not putting a '/' in the previous state. */
                buffer[i] = '/';
                ++i;
                state = STATE_OUT; /* Back to normal. */
            }
        }
        else if (state == STATE_IN_COMMENT) {
            /* Wait until a hint of comment end... */
            if (c == '*') {
                /* Set state to listen to a '/' on next char. */
                state = STATE_END_COMMENT;
            }
        } 
        else if (state == STATE_END_COMMENT) {
            /* See if comment did indeed end. */
            if (c == '/') {
                /* Comment ended alright. However, we don't want the last
                 * '/'. So, we raise the `skipflag` and leave the comment. */
                state = STATE_OUT;
                skipflag = TRUE;
            }
            else {
                /* Nope, comment didn't end, back to comment. */
                state = STATE_IN_COMMENT;
            }
        }
        else if (state == STATE_IN_STRING) {
            /* Wait for the string to end... */
            if (c == '"') {
                state = STATE_OUT;
            }
        }
        else if (state == STATE_IN_CHAR) {
            /* Wait for the char to end... */
            if (c == '\'') {
                state = STATE_OUT;
            }
        }

        if (
            skipflag != TRUE
            && state != STATE_IN_COMMENT
            && state != STATE_BEGIN_COMMENT
            && state != STATE_END_COMMENT
        ) 
        {
            /* Check if we have buffer space first, and try to place a char.*/
            if (i < length-1) {
                buffer[i] = c;
                ++i;
            }
            else {
                /* No space. Cache the char and put it next time. */
                bufferchar = c;
            }
        } 
    }

    /* End the string. */
    buffer[i] = '\0';
    
    /* Return the length. */
    return i;
}

int main() {
    char buffer[MAXBUFFER];
    int result;

    while((result=stripcomments(buffer, MAXBUFFER)) > 0) {
        printf("%s", buffer);
    }

    return result;
}

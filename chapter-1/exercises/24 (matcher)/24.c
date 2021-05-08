/* NOTE: The Book didn't yet cover structures or pointers and they have been 
 * deliberately not used.
 * This has been a rule up until now too, but in this particular
 * case, the side effects of this are more prominent. 
 * Perhaps the worst side effect is keeping the symbol stack along
 * with the line number and character count in three separate arrays.
 * Also, to keep track of the escape sequence state, a separate array of three
 * elements is used.
 * -------------------------------------------------------------------------- */

#include <stdio.h>

#define FALSE 0
#define TRUE  1
#define BOOL  int

#define STATE_OUT              0 
#define STATE_IN_COMMENT       1 
#define STATE_IN_STRING        2 
#define STATE_IN_CHAR          3 
#define STATE_BEGIN_COMMENT    4 
#define STATE_END_COMMENT      5 
#define STATE_FAKE_END_COMMENT 6 /* For catching redundant comment ends. */

#define MAXSTACK 99999

#define ERROR_SYMBOL_STACK_OVERFLOW -1


/* Swap routines. C won't let overrides, so need a version for each type.
 * -------------------------------------------------------------------------- */
void swapchars(char s[], int idxa, int idxb) {
    s[idxa] = s[idxa] + s[idxb];
    s[idxb] = s[idxa] - s[idxb];
    s[idxa] = s[idxa] - s[idxb];
}
void swapints(int s[], int idxa, int idxb) {
    s[idxa] = s[idxa] + s[idxb];
    s[idxb] = s[idxa] - s[idxb];
    s[idxa] = s[idxa] - s[idxb];
}
/* -------------------------------------------------------------------------- */


/* Couple of helpers for open/close char pairs. 
 * -------------------------------------------------------------------------- */
char getopening(char closing) {
    if (closing == ')') {
        return '(';
    }
    if (closing == '}') {
        return '{';
    }
    if (closing == ']') {
        return '[';
    }
    return closing;
} 

BOOL isopeningchar(char c) {
    return c == '(' || c == '{' || c == '[';
} 
BOOL isclosingchar(char c) {
    return c == ')' || c == '}' || c == ']';
}
/* -------------------------------------------------------------------------- */


/* Submit a character into the matching 'engine'. 
 * Will place opening characters into the given stack, and try to match
 * closing characters with the ones in the stack. 
 * Returns the updated stack iterator.
 * -------------------------------------------------------------------------- */
int processchar(
    char c,           /* Character to place. */
    int line,         /* Current line. */
    int column,       /* Current column. */
    char stack[],     /* Opening Symbol stack. */
    int stacklines[], /* Companion to stack, keep line nums for each char. */
    int stackcols[],  /* Companion to stack, keep col nums for each char. */
    int stacki        /* Current stack iterator. */
) 
{
    int i;
    BOOL ismatch;
    
    /* If we have an opening char, place it in the stack. */
    if (isopeningchar(c)) {
        stack[stacki] = c;
        stacklines[stacki] = line;
        stackcols[stacki] = column;
        ++stacki;

        /* Panic if we hit stack limit -- cannot really guarantee 
         * correctness if we were to continue. */
        if (stacki >= MAXSTACK) {
            fprintf(
                stderr, 
                "[!] Error: symbol stack overflow. Terminating.\n"
                "    Stack size was %i.\n"
                , MAXSTACK);
            return ERROR_SYMBOL_STACK_OVERFLOW;
        }
    }
    else if (isclosingchar(c)) {
        /* If stack is empty, obviously unmatched. */
        if (stacki == 0) {
            printf("stdin: %2i:%2i: error: Unmatched `%c`.\n", line, column, c);
        }
        else {
            /* Otherwise, we should search the stack for an opening pair for this 
             * character. First, easy case: check the top of the stack.*/
            if (stack[stacki-1] == getopening(c)) {
                --stacki;
            }
            else {
                ismatch = FALSE;
                for (i = stacki-1; i >= 0 && ismatch == FALSE; --i) {
                    if (stack[i] == getopening(c)) {
                        swapchars(stack, i, stacki-1);
                        swapints(stacklines, i, stacki-1);
                        swapints(stackcols, i, stacki-1);
                        --stacki;

                        ismatch = TRUE;
                    }
                }
                if (ismatch == FALSE) {
                    printf("stdin: %2i:%2i: error: Unmatched `%c`.\n", line, column, c);
                }
            }
        }
    }
    return stacki;
}

/* Update the state of the input so far, where state is one of the 
 * STATE_* macros above. 
 * Will also attempt to match escape sequences and print to stdout in case
 * of mismatches.
 * Note about `escapeinfo` parameter:
 * This array must have exactly 3 integer items with following semantics:
 * { is_currently_in_escape_sequence, `\`-line num, `\`-column num }
 * -------------------------------------------------------------------------- */
int stateprocess(char c, int state, int escapeinfo[], int line, int charcounter) {
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

        /* If we have a star, we might be ending an unstarted comment. */
        if (c == '*') {
            state = STATE_FAKE_END_COMMENT;
        }
    }
    else if (state == STATE_BEGIN_COMMENT) {
        /* See if it's indeed a comment. */
        if (c == '*') {
            state = STATE_IN_COMMENT;
        }
        else {
            /* Not a comment afterall. */
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
            /* Comment ended alright. */
            state = STATE_OUT;
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
            /* Report if we were in string and didn't finish escape sequence. */
            if (escapeinfo[0]) {
                printf("stdin: %2i:%2i: error: Unmatched `\\`.\n", line, charcounter-1); 
                escapeinfo[0] = FALSE;
            }
        }
    }
    else if (state == STATE_IN_CHAR) {
        /* Wait for the char to end... */
        if (c == '\'') {
            state = STATE_OUT;
            /* Report if we were in char and didn't finish escape sequence. */
            if (escapeinfo[0]) {
                printf("stdin: %2i:%2i: error: Unmatched `\\`.\n", line, charcounter-1); 
                escapeinfo[0] = FALSE;
            }
        }
    }
    else if (state == STATE_FAKE_END_COMMENT) {
        /* Report if it's an end comment, but we don't have a start comment. */
        if (c == '/') {
            printf("stdin: %2i:%2i: error: Unmatched `*/`.\n", line, charcounter-1);
        }
        state = STATE_OUT;
    }
   
    /* If we are in string/char, we can begin */ 
    if (state == STATE_IN_CHAR || state == STATE_IN_STRING) {
        /* If we started the escape sequence already */
        if (escapeinfo[0]) {
            if 
            (
               /* If it's not any of below chars, we can say 
                * the escape sequence is not matched. */
               !((c >= 48 && c <= 57)    /* Numeric */ 
                || (c >= 65 && c <= 90)  /* Capital letters */
                || (c >= 97 && c <= 122) /* Small letters */
                || (c == '\\'))          /* Actual `\` is valid too. */
            ) 
            {
                printf(
                    "stdin: %2i:%2i: error: Unmatched `\\`.\n", 
                    escapeinfo[1], 
                    escapeinfo[2]
                ); 
            }
            escapeinfo[0] = FALSE;
        }
        /* If we didn't start the escape sequence and the char is `\`, 
         * we raise the flag and store the position. */
        else if (c == '\\') {
            escapeinfo[0] = TRUE;
            escapeinfo[1] = line;
            escapeinfo[2] = charcounter;
        }
    }

    return state;
}

int main() {
    /* Keep opening symbols in a stack-like structure. 
     * Try to match closing symbols with them. */
    char stack [MAXSTACK];
    /* Keep two companion arrays to keep track of character positions. */
    int stacklines[MAXSTACK], stackcols[MAXSTACK];
    
    int c, prevstate, state, stacki, line, col;
    stacki = col = 0;
    state = STATE_OUT;
    line = 1;
   
    /* Keep this for an edge case where we are kept in some weird state
     * on input end. For reporting the position where we entered that state.*/ 
    int statechangeline, statechangecol;

    /* Please see `stateprocess` documentation for a semi-sane explanation... */
    int escapeinfo[3] = { FALSE, 0, 0 };

    while ((c=getchar()) != EOF) {
        ++col;
        if (c == '\n') {
            ++line;
            col = 0;
        }

        /* Process current state with current char. See if we entered a
         * comment, or string, or char, etc. Also does escape sequence 
         * matching inside... Not good. But oh well. */
        prevstate = state;
        if (prevstate != (state=stateprocess(c, state, escapeinfo, line, col))) {
            statechangeline = line;
            statechangecol = col-1; 
        }

        /* Only match characters if we are not in comment, string, etc. */
        if (state == STATE_OUT) {
            stacki = processchar(
                c,
                line,
                col,
                stack,
                stacklines,
                stackcols,
                stacki        
            );

            if (stacki == ERROR_SYMBOL_STACK_OVERFLOW) {
                return 1;
            }
        }
    }

    /* If we have no more input, just dump contents of stack, because
     * the symbols left are essentially unmatched. */
    while (stacki > 0) {
        --stacki;
        printf(
            "stdin: %2i:%2i: error: Unmatched `%c`.\n", 
            stacklines[stacki], 
            stackcols[stacki], 
            stack[stacki]
        );
    }

    /* See if we are left in some unusual state and report this. */
    if (state == STATE_IN_STRING) {
        printf(
            "stdin: %2i:%2i: error: Unmatched `\"`.\n",
            statechangeline,
            statechangecol
        );
    }
    if (state == STATE_IN_CHAR) {
        printf(
            "stdin: %2i:%2i: error: Unmatched `'`.\n",
            statechangeline,
            statechangecol
        );
    }
    if (state == STATE_IN_COMMENT) {
        printf(
            "stdin: %2i:%2i: error: Unmatched `/*`.\n",
            statechangeline,
            statechangecol
        );
    }

    return 0;
}


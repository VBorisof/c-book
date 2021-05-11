/* Ex.1-19
 * Write a function reverse(s) that reverses the character string s. 
 * Use it to write a program that reverses its input a line at a time.
 * -------------------------------------------------------------------------- */

#include <stdio.h>
#define MAXLINE 1000

/* A swap routine. No temp vars. */
void swap(char s[], int idxa, int idxb) {
    s[idxa] = s[idxa] + s[idxb];
    s[idxb] = s[idxa] - s[idxb];
    s[idxa] = s[idxa] - s[idxb];
}

/* Reverses the string, ignoring the NL character (leaves it at its' place). */
void reverse(char s[]) {
    int i, j;
    for(i = 0; s[i+1] != '\n'; ++i) {
        /* Just keep count */
    }

    for (j = 0; i > j; --i) {
        swap(s, i, j);
        ++j;
    }
}

/* 
 * Read from standard input into a provided 
 * character array of given maximum length. 
 * */
int mygetline(char line[], int maxline) {
    int c, i;
    for (i = 0; i<maxline && (c=getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = '\n';
        ++i;
    }

    line[i] = '\0';

    return i;
}

int main() {
    char line[MAXLINE];
    while(mygetline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

#include <stdio.h>

#define MAXLINE 1000

int mygetline(char line[], int maxline);
void mycopy(char to[], char from[]);

/* Read the line into given array, return length. */
int mygetline(char line[], int maxline) {
    int c, i; 
    for (i = 0; i<maxline-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
} 

/* Copy `from` into `to`. Assumes `to` is big enough. */
void mycopy(char to[], char from[]) {
    int i;
    i = 0;

    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            mycopy(longest, line);
        }
    }

    if (max > 0) {
        printf("Longest line: %s (%d)\n", longest, max);
    }
    return 0;
}

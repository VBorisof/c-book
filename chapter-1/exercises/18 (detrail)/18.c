#include <stdio.h>
#define MAXLINE 1000

/* Feed a line from standard input into the given char array of given maxsize
 * and remove all the trailing tabs and whitespaces from the end of the line.
 * */
int getlinenotrail(char outchars[], int maxline) {
    int i, c;

    /* First store all the chars until we hit maxline or encounter EOF or NL. */
    for (i = 0; i<maxline-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        outchars[i] = c;
    }
  
    /* Then, start going backwards, deleting every damn excess blank we see in the way. */
    for (i = i-1; i >= 0 && (outchars[i] == '\t' || outchars[i] == ' '); --i) 
    {
        /* Do nothing here, just let the counter go... */
    }
    ++i;
    
    /* Finally, end the line. */
    if (c == '\n') {
        outchars[i] = '\n';
        ++i;
    }
    outchars[i] = '\0';

    return i;
}

int main() {
    char line[MAXLINE];

    while (getlinenotrail(line, MAXLINE) > 0) {
        printf("%s", line);
    }
}

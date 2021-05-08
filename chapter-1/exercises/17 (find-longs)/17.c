#include <stdio.h>
#define MAXLINE 1000
#define MINLINE 80

int mygetline(char outchars[], int minline, int maxline) {
    int i, c;
    for (i = 0; i<maxline-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        outchars[i] = c;
    }

    if (c == '\n') {
        outchars[i] = c;
        ++i;
    }
    
    outchars[i] = '\0';
    return i;
}

int main() {
    char line[MAXLINE];
    int currentlen = 0;

    while ((currentlen=mygetline(line, MINLINE, MAXLINE)) > 0) {
        if (currentlen > MINLINE) {
            printf(">80: %s\n", line);
        }
    }
}

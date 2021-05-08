#include <stdio.h>

#define MAXLINE 100

int mygetline(char line[], int maxline) {
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
        if (i < maxline-1) {
            line[i] = c;
        }
    }

    if (c == '\n' && i < maxline-1) {
        line[i] = c;
        ++i;
    }
    
    if (i < maxline-1){
        line[i] = '\0';
    }
    else {
        line[maxline-1] = '\0';
    }
    return i;
}

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
        if (max > MAXLINE) {
            printf("Longest line: %s... (%d)\n", longest, max);  
        }
        else {
            printf("Longest line: %s (%d)\n", longest, max);      
        }
    }
    

    return 0;
}

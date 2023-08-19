// Print the longest line
#include <stdio.h>
#define MAXLINE 1000

int getline0(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = getline0(line, MAXLINE)) > 0)
    {
        if (len > 80)
            printf("Len is %d from: %s", len, line);
    }
    return 0;
}

int getline0(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
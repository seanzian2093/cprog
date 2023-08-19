// Print the longth of input lines and as much as possbile of the text
#include <stdio.h>
#define MAXLINE 1000

int getline0(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline0(line, MAXLINE)) > 0)
    {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
        printf("Len: %d from %s", len, line);
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

void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        i++;
    }
    
}
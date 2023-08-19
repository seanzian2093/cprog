// Print the longest line
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline0(char line[], int maxline);
char * reverse(char line[], char tmp[]);

int main(void)
{
    int len;
    char line[MAXLINE];
    char tmp[MAXLINE];

    while ((len = getline0(line, MAXLINE)) > 0)
    {
        printf("Input line: %s\n", line);
        reverse(line, tmp);
        printf("Reversed line: %s\n", tmp);
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
char * reverse(char line[], char tmp[])
{
    int n;
    n = strlen(line);
    // printf("len is: %d\n", n);

    for (int i = 0; i < n-1; i++)
        tmp[n-2-i] = line[i];
    
    tmp[n-1] = '\0';
    // printf("tmp: %s\n", tmp);
    return 0;
}
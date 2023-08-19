// Search for a pattern in text
#include <stdio.h>
#define MAXLINE 1000

int getline0(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main(void)
{
    // Find all lines matching pattern
    char line[MAXLINE];
    int found = 0;
    while (getline0(line, MAXLINE) > 0 )
    {
        int k = strindex(line, pattern);
        if (k >= 0)
        {
            printf("Pattern found at %d postion of %s", k, line);
            found++;
        }
    }
    printf("Patterns found: %d\n", found);
    return found;
}

int getline0(char s[], int lim)
{
    int c, i;
    i = 0;
    // ensure lim > 0
    // keep receiving untill newline
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }

    // take newline as well
    if  (c == '\n')
        s[i++] = c;
    // add null
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[])
{
    int i, j, k;
    // compare 0 to n-1 of s against t; then 1 to n, then 2 to n+1
    // n is the length of t
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k];j++, k++)
            ;
        // ensure t is at least 1 char and reached end
        if (k > 0 && t[k] == '\0')
            return i + k -1;
    }
    return -1;
}

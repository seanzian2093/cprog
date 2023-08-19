// remove trailing blanks, tabs, newlines.
#include <stdio.h>
#include <string.h>

int trim(char s[]);
void reverse(char s[]);

int main(void)
{
    char s[10];
    printf("Please input a string as s: ");
    scanf("%s", s);
    trim(s);
    printf("After trim, s is: %s\n", s);
}

int trim(char s[])
{
    int n;
    for (n = strlen(s) - 1; n >= 0; n--)
        // if last char is not the target, trimming is completed, put next char as '\0`
        if (s[n] != ' ' || s[n] != '\t' || s[n] != '\n')
            break;
        // if last char is target, n is reduced by 1,i.e. move to left
    s[n+1] = '\0';
    return n;
}

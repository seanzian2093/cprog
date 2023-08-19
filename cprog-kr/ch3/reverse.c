// Reverse a string in place
#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(void)
{
    char s[10];
    printf("Please input a string as s: ");
    scanf("%s", s);
    reverse(s);
    printf("After reverse, s is: %s\n", s);
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
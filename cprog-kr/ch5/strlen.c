// Return length of string s

#include <stdio.h>
int strlen0(char *s);

int main(void)
{
    char s[20];
    printf("Please input: ");
    scanf("%s", s);
    printf("You input is of length: %d\n", strlen0(s));
}

int strlen0(char *s)
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}
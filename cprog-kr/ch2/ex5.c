// Delete each character in s that matches any character in t
#include <stdio.h>
#include <string.h>

int match(char s[], int c);
int any(char s[], char t[]);

int main()
{
    char s[20], t[20];
    printf("Please input s: ");
    scanf("%s", s);
    printf("Please input t: ");
    scanf("%s", t);
    int ret;
    ret = any(t, s);
    printf("First location is: %d\n", ret);
}

int any(char s[], char t[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (match(t, s[i]))
            break;
    }
    return ++i;
}

int match(char s[], int c)
{
    int n, i;
    for (i = n = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
            n++;
    }
    return n;
}
// Delete each character in s that matches any character in t
#include <stdio.h>
#include <string.h>

int match(char s[], int c);

int main()
{
    char s[20], t[20];
    printf("Please input s: ");
    scanf("%s", s);
    printf("Please input t: ");
    scanf("%s", t);
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
    {
        if (!match(t, s[i]))
            s[j++] = s[i];
    }
    s[j] = '\0';
    printf("After deletes, s is now: %s\n", s);
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
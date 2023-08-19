// Converts hexadecimal digits to integer
#include <stdio.h>
#include <string.h>

long int htoi(char s[]);
int main(void)
{
    long int i;
    char s[20];
    // if user input is larger than 20, some memory related error/warning will occur
    scanf("%s", s);
    i = htoi(s);
    printf("%ld\n", i);
}
long int htoi(char s[])
{
    int i, l;
    long int n;
    n = 0;
    l = strlen(s);
    for (i = 0; i < 64 && i <= l; i++)
    {
        // if (s[i] >= '0' && s[i] <= '9' && s[i] != 'x' && s[i] != 'X')
        if (s[i] >= '0' && s[i] <= '9')
        {
            n = 16 * n + (s[i] - '0');
            // printf("%c\n", s[i]);
        }
        else if (s[i] >= 'a' && s[i] <= 'f')
        {
            n = 16 * n + (s[i] - 'a') + 10;
            // printf("%c\n", s[i]);
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            n = 16 * n + (s[i] - 'A') + 10;
            // printf("%c\n", s[i]);
        }
    }
    return n;
}

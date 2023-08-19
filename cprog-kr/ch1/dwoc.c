// Count digits, white spaces, and others

#include <stdio.h>

int main(void)
{
    int c, i, nwhite, nother;
    int ndigits[10];

    nother = nwhite = 0;

    for (i = 0; i < 10; i++)
        ndigits[i] = 0;

    while ((c = getchar()) != EOF)
    {
        // in C, chars are jsut small integers so chars adn constants are identical to ints in airhtmetic expressions.
        // '0', '1', ... ,'9' have consecutive increasing values.
        if (c >= '0' && c <= '9')
           ndigits[c-'0']++;
        else if (c == ' ' || c == '\n' || c == '\t')
            nwhite++;
        else
            nother++;
    }
    printf("digits =");
    for (i = 0; i < 10; i++)
        printf(" %d", ndigits[i]);

    printf(" , white space = %d, other = %d\n", nwhite, nother);
    
}
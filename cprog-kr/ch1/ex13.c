// Print a histogram of the lengths of words in its input

#include <stdio.h>

int main(void)
{
    int c, nc, i;
    nc = 0;

    while ((c=getchar()) != EOF)
    {
        nc++;
        if (c == ' ' || c == '\n' || c == '\t')
        {
            // single quote for single character, i.e small integer
            // Double quotes for string literal, i.e. an array of char and null terminator \0
            // 'x' is a single char; "x" is an array of 'x' and '\0'
            printf(": ");
            for (i = 0; i < nc; i++)
                printf("#");
            printf("\n");
            nc = 0;
        }
        else
            putchar(c);
    }
    
}
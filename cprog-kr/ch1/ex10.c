// Exercise 10 - replacing 

#include <stdio.h>

int main()
{
    int c;
    int prex = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            prex = '\\';
            c = 't';
        }
        else
            prex = 0;
        putchar(prex);
        putchar(c);
    }
}
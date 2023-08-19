// Exercise 8 - Count tabs, blanks, and newlines

#include <stdio.h>

int main()
{
    int c, tbn;

    tbn = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == '\b' || c == '\t')
            tbn++;
    }
    printf("%d\n", tbn);
    
}
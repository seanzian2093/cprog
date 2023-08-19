// Converts input to lower case
#include <stdio.h>
#include <ctype.h>

// Convert input to lower case
int main(void)
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(tolower(c));
    return 0;
}
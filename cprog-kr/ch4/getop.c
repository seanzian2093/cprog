// Fetch next operator or operand
#include <ctype.h>
#include <stdio.h>
#include "calc.h"

// Get next char or numeric operand
int getop(char s[])
{
    int i, c;
    // Skip blank or tab
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // If char, get it as operator
    if (!isdigit(c) && c != '.')
        return c;
    // Otherwise get digits
    i = 0;
    if (isdigit(c))
        // Collect integer part
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        // Collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER; 
}
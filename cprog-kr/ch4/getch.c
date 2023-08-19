// Define getch() and ungetch() functions
#include <stdio.h>

#define BUFSIZE 100

// Buffer for ungetch
static char buf[BUFSIZE];
// Next free positiion in buf
static int bufp = 0;

// Get a (possibly pushed-back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push character back on input
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
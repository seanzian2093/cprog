// Get next integer from input into *pn
#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100
#define SIZE 100

// Buffer for ungetch
static char buf[BUFSIZE];
// Next free positiion in buf
static int bufp = 0;

int getch(void);
void ungetch(int);
int n, array[SIZE], getint(int *pn);

int main(void)
{
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        printf("The %d-th elment of array is: %d\n", n, array[n]);
}

int getint(int *pn)
{
    int c, sign;
    // Skip white space
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-');
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

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
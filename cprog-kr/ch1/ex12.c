// Print input one word per line
#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
    int c, state;
    state = OUT;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        if (c == ' ' || c == '\t' || c =='\n') {
            state = OUT;
            printf("\n");
        }
        else if (state == OUT) {
            state = IN;
        }
    }
}
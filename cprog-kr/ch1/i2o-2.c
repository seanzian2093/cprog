// Second version - copying input to output
// More concise

#include <stdio.h>

int main(void)
{
    int c;

    // define and refer c simultaneously in while condition
    // != operator has higher precedence
    while ((c = getchar()) != EOF)
        putchar(c);
}
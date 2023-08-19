// First version - copying input to output

#include <stdio.h>

int main(void)
{
    int c;
    // getchar() prompts user to input a character once a time until EOF
    c = getchar();
    // Ctrl + D to input EOF
    while (c != EOF)
    {
        putchar(c);
        c = getchar();
    }
    
}
// Second version - copying input to output
// More concise
// exercise 6

#include <stdio.h>

int main(void)
{
    int c;
    while ((c = getchar()) != EOF)
    {
        printf("getchar() != EOF: %d\n", c != EOF);
    }
}
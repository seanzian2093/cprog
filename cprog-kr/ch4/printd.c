// Print n in decimal

#include <stdio.h>

void printd(int n);

int main(void)
{
    int i = 12345, j = -12345;
    printd(i);
    printf("\n");
    printd(j);
    printf("\n");
}

void printd(int n)
{
    // Handle sign
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    // if n/10 >= 1; integer division, faction is discarded;
    if (n / 10)
        // Use printd recursively
        printd(n / 10);
    putchar(n % 10 + '0');
}
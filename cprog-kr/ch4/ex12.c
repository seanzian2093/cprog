// Convert an integer into a string by calling a recursive routine

#include <stdio.h>

void itoa(int n, char s[]);

int main(void)
{
    int i = 12, j = -12;
    // int i = 1, j = -1;
    char s[20];
    itoa(i, s);
    printf("%d is converted to %s\n", i, s);
    // itoa(j, s, 0);
    // printf("%d is converted to %s\n", j, s);
}

void itoa(int n, char s[])
{
    int d, i, tmp;
    i = 0;
    // Handle sign
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    // Determine number of digits
    for (i = i, tmp = n; (tmp / 10) > 0; i++)
        tmp /= 10;
    // if n/10 >= 1; integer division, faction is discarded;
    if (n / 10) {
        // Use printd recursively
        itoa(n / 10, s);
    }
    d = n % 10;
    s[i] = d + '0';
    printf("put %d in position %d\n", d, i);
    s[i+1] = '\0';
}

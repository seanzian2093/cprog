// Raise base to n-th power
#include <stdio.h>

// Parameter names are optional for function declaration
int power(int m, int n);

int main(void)
{
    int i;
    for (i = 0; i < 10; i++)
        printf("%d %d %d\n", i, power(2,i), power(-3,i));
    
    return 0;
}

// Parameter names do not have to agree with declaration
int power(int base, int n)
{
    int p;
    for (p = 1; n > 0; n--)
        p = p * base;
    return p;
}
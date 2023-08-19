// User assert() to terminate program intentionally

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int isprime(int);

int main(int argc, char * argv[])
{
    int i, j;
    assert(argc >= 2);
    for (i = 1; i < argc; i++)
    {
        j = atoi(argv[i]);
        if(isprime(j) != 0)
            printf("%d is prime\n", j);
    }
}

int isprime(int val)
{
    int i;
    assert(val >= 2);
    for (i = 2; i < val; ++i)
        if (val % i == 0)
            return 0;
    return 1;
}
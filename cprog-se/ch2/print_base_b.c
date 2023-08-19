// Convert decimal value x to a representation in base b

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_base_b(unsigned, unsigned);

int main(int argc, char * argv[])
{
    assert(argc >= 3);

    unsigned x = (unsigned) atoi(argv[1]);
    unsigned b = (unsigned) atoi(argv[2]);

    print_base_b(x, b);

    return 0;
}

void print_base_b(unsigned x, unsigned b)
{
    char buf[BUFSIZ];

    int q = x, i = 0;
    assert(b >= 2);

    do {
        assert(i < BUFSIZ);
        x = q;
        q = x / b;
        buf[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[x - q * b];
    } while (q > 0);
    
    for (--i; i >= 0; --i)
        printf("%c", buf[i]);
    printf("\n");
}
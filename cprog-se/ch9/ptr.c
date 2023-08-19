// Pointers in C.C++ freeCodeCamp.org@in youtube

#include <stdio.h>

int main(void)
{
    int a;
    int *p;
    p = &a;

    a = 10;
    // print mem address in decimal but truncated to int
    printf("%d\n", p);
    // print mem address in decimal, equals to hexadecimal address concerted to decimal
    printf("%ld\n", p);
    printf("%d\n", *p);
    printf("%p\n", p);
    printf("%d\n", &a);
    printf("%ld\n", &a);
}
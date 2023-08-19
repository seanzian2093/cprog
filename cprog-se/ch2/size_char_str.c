// Size of a char and a string of one char

#include <stdio.h>

int main(void)
{
    // sizeof returns a long int
    printf("Size of 'x': %ld\n", sizeof('x'));
    printf("Size of \"x\": %ld\n", sizeof("x"));
}
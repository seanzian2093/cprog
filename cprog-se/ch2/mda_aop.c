// Show mult-dim arrays and arrays of pointers may be used in identical fashion

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    assert(argc > 2);
    int i = atoi(argv[1]);
    int j = atoi(argv[2]); 
    // a and b are array, also a pointer to its first element location
    char a[] = { 1, 2, 3 };
    char b[] = { 4, 5, 6 };
    // c is an array of pointers
    char *c[] = { a, b };
    // d is 2-d array with rows unspecified
    char d[][3] = { { 1, 2, 3 }, { 4, 5, 6 } };

    printf("The value at (%d, %d) of c: %d\n", i, j, c[i][j]);
    printf("The value at (%d, %d) of d: %d\n", i, j, d[i][j]);
}
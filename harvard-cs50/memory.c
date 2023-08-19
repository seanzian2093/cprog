#include <stdlib.h>
#include <stdio.h>

void f(void);

int main(void) {
    f();
}

void f(void) {
    // size of int is 4 bytes, 32 bits
    // malloca return a pointer at the memory allocated
    int *x = malloc(10 * sizeof(int));

    // memory is like an array
    // assign value out of bound will cause memory related error
    // x[10] = 50;
    x[9] = 50;
    printf("You inputted %i\n", x[9]);
    // value from outbound address is garbage
    printf("You inputted %i\n", x[10]);
    // always free with malloc - takes memory address
    free(x);
    // TODO - why x still has values after free()
    // free(x) just label x as available but does nothing to the values there?
    printf("After free(x) %i\n", x[9]);
    printf("After free(x) %i\n", x[8]);
}
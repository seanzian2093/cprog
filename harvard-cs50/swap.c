#include <stdio.h>
#include <string.h>

void swap(int *a, int *b);

int main(void) {
    int x = 1;
    int y = 2;
    printf("x is %i, y is %i\n", x, y);
    // when passing x and y to swap, their copies, i.e. values are passed;
    // x and y are not changed by swap but their copies.
    // when referencing, &a means getting the address at the memory address define by e.g. int *a
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

// pass address of a and b, not their values
// when referencing, *a means getting the value at the memory address define by e.g. int *a
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
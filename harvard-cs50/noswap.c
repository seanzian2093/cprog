#include <stdio.h>
#include <string.h>

void swap(int a, int b);

int main(void) {
    int x = 1;
    int y = 2;
    printf("x is %i, y is %i\n", x, y);
    // when passing x and y to swap, their copies, i.e. values are passed;
    // x and y are not changed by swap but their copies.
    swap(x, y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
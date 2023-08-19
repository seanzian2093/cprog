#include <stdio.h>
#include <string.h>

int main(void) {
    int x;
    printf("x: ");
    scanf("%d", &x);
    printf("x is: %i\n", x);
    printf("x is stored at: %p\n", &x);
}
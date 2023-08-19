#include <stdio.h>
#include <string.h>

int main(void) {
    // explicitly decline an array of char, with length 6
    char s[6];
    printf("s: ");
    // array of char can be treated as pointer
    scanf("%s", s);
    printf("s is: %s\n", s);
    printf("s is stored at: %p\n", &s);
}
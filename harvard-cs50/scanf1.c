#include <stdio.h>
#include <string.h>

int main(void) {
    // since s is a pointer at NULL so no memory space for strings to store there
    char *s = NULL;
    printf("s: ");
    scanf("%s", s);
    printf("s is: %s\n", s);
    printf("s is stored at: %p\n", &s);
}
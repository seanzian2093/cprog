// Dynamically allocate a copy of string. User must remember to free this memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_duplicate(char *);

int main(void)
{
    char s[20], *t;
    printf("Enter a string: ");
    scanf("%s", s);
    t = string_duplicate(s);
    printf("The string you just entered is: %s\n", t);

    // t is a pointer to memory dynamically allocated, should be freed when not needed;
    free(t);
    return 0;
}

char *string_duplicate(char *s)
{
    char *p;
    // If successful, malloc() return a pointer to void, and then cast to pointer to char type
    // If fail, malloc() return NULL
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    
    // p is a pointer to memory dynamically allocated, should be freed when not needed;
    return p;
}
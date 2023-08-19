// C programming in Linux - ch2_2

#include <stdio.h>

int main(void)
{
    char c1 = 'd';
    char c2 = 'a';
    char c3 = 'v';
    char c4 = 'i';
    char c5 = 'd';
    char name[6] = "";

    // Send formatted output to a string
    sprintf(name, "%c%c%c%c%c", c1, c2, c3, c4, c5);
    printf("%s\n", name);
}

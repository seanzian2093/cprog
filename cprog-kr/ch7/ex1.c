// Converts input to lower case or to upper case, depending on name it is invoked with
#include <stdio.h>
#include <ctype.h>

// Convert input to lower case
int main(int argc, char *argv[])
{
    int c;
    while ((c = getchar()) != EOF)
        // *argv is the 1st element of argv
        // it is like ./ex1 so first 2 character should be ignored
        if ((*argv)[2] == 'l')
            putchar(tolower(c));
        else
            putchar(toupper(c));
    return 0;
}
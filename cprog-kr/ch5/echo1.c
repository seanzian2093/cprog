// Illustrate how c programm handles command line arguments - second version
#include <stdio.h>

// Echo command line arguments
int main(int argc, char *argv[])
{
    int i;
    // argc is the count of arguments
    // argv is the vector of arguments, i.e. a pointer to an array
    // argv[0] is the programm name which is evoked, so argc >= 1
    while (--argc > 0)
        // Manipulate pointer instead of array indices
        printf("%s%s", *++argv, (argc > 1 ? " " : ""));
    printf("\n");
    return 0;
}
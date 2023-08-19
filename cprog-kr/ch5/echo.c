// Illustrate how c programm handles command line arguments - first version
#include <stdio.h>

// Echo command line arguments
int main(int argc, char *argv[])
{
    int i;
    // argc is the count of arguments
    // argv is the vector of arguments, i.e. a pointer to an array
    // argv[0] is the programm name which is evoked, so argc >= 1
    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc-1 ? " " : ""));
    printf("\n");
    return 0;
}
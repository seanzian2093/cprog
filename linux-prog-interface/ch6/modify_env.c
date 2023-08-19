// Modify the process environment
// To get various declarations from <stdlib.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

extern char **environ;

int main(int argc, char *argv[])
{
    int j;
    // A pointer to pointer to hold env variables
    char **ep;

    // Erase entire environment
    clearenv();

    for (j = 1; j< argc; j++)
        if (putenv(argv[j]) != 0)
            errExit("putenv: %s", argv[j]);
    if (setenv("GREET", "Hello world", 0) == -1)
        errExit("setenv");
    unsetenv("BYE");

    // Print out each env
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
    
    exit(EXIT_SUCCESS);
}

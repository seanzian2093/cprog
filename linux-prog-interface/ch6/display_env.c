// Display the process environment

#include "tlpi_hdr.h"

// environ is a global varialble
extern char **environ;

// Could also use a third arg to main() to refer to environment variables but only local to main()
int main(int argc, char *argv[])
{
    char **ep;
    for (ep=environ; *ep != NULL; ep++)
        puts(*ep);
    exit(EXIT_SUCCESS);
}
// Passing the caller's environment to the new program using execl()

#include <stdlib.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    printf("Initial value of USER: %s\n", getenv("USER"));
    if (putenv("USER=Emma") != 0)
        errExit("putenv");
    
    execl("/usr/bin/printenv", "printenv", "USER", "SHELL", (char *) NULL);
    errExit("execl");
}
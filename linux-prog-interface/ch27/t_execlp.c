// Using execlp() to search for a filenaem in PATH

#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    // 1st arg of execlp() is the FILE to be searched in PATH; if it starts with '/', it is ignored
    // 2nd arg is the argv[0] of the main() of new program to be executed
    // 3rD arg to last NULL are args provided to 2nd arg
    execlp(argv[1], argv[1], "hello world", (char *) NULL);
    errExit("execlp");
}
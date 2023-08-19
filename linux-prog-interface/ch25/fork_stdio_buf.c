// Interaction of fork() and stdio buffering
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    // when stdout is directed to a terminal, it is line-buffered by default, so the newline-terminated string 
    // written by prinf() appears immediately, and not copied to child by fork().

    // When stdout is directedto a file, it is block buffered by default. so when fork(), the string is still buffered
    // thus copied to child. when exit() it is flushed
    printf("Hello world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    if (fork() == -1)
        errExit("fork");
    
    exit(EXIT_SUCCESS);
}

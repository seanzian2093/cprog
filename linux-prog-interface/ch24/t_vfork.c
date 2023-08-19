// Using vfork()

#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    // Allocated in stack segment
    int istack = 222;

    switch(vfork())
    {
        case -1:
            errExit("vfork");
        
        // Child executes first in parent's memory space
        case 0:
            // Even if child sleep for a while, parent is still not scheduled
            sleep(3);
            write(STDOUT_FILENO, "Child executing\n", 16);
            // This change will be seen by parent; Child shares the parent's memory untill _exit() or exec()
            istack *= 3;
            _exit(EXIT_SUCCESS);
        
        // Parent is blocked until child exits
        default:
            write(STDOUT_FILENO, "Parent executing\n", 17);
            printf("istack=%d\n", istack);
            exit(EXIT_SUCCESS);
    }
}
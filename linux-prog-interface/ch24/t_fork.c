// Using fork()

#include "tlpi_hdr.h"
#include "error_functions.c"

// Allocated in data segment
static int idata = 111;

int main(int argc, char *argv[])
{
    // Allocated in stack segment
    int istack = 222;
    pid_t childPid;

    switch(childPid = fork())
    // For here on, both parent and child exist and continue execution
    // For parent childPid is the newly created child process id; for child it is 0
    {
        // Handle error when fork()
        case -1:
            errExit("fork");
        // For child, childPid is 0 
        case 0:
            idata *= 3;
            istack *= 3;
            break;
        // For parent, childPid is child process id, neither -1 or 0 if success 
        default:
            // Suspend parent process to give child process a chance to execute
            sleep(3);
            break;
    }

    // For parent childPid is the newly created child process id; for child it is 0
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), (childPid == 0) ? "(child)" : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
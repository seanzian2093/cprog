// Using fork() but parent does not sleep(3)
// Since Linux 2.6.32 parent process run first after a fork(). This default can be changed by assigning a nonzero
// value to the Linux-specific /proc/sys/kernel/sched_child_runs_first file.

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
            // Parent does not sleep see what happens
            // sleep(3);
            idata *= 2;
            istack *= 2;
            break;
    }

    // For parent childPid is the newly created child process id; for child it is 0
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), (childPid == 0) ? "(child)" : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
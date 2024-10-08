// Using clone() to create a child process

#define _GNU_SOURCE
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sched.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1
#endif

static int childFunc(void *arg)
{
    if (close(*((int *) arg)) == -1)
        errExit("close");
    
    return 0;
}

int main(int argc, char *argv[])
{
    const int STACK_SIZE = 65536;
    char *stack;
    char *stackTop;
    int s, fd, flags;

    // Create a file descriptor for child to close
    fd = open("/dev/null", O_RDWR);
    if (fd == -1)
        errExit("close");

    // If argc > 1, child shares file descriptor table with parent
    flags = (argc > 1) ? CLONE_FILES : 0;

    // Allocate stack for child
    stack = malloc(STACK_SIZE);
    if (stack == NULL)
        errExit("malloc");
    // Assume stack grows downward
    stackTop = stack + STACK_SIZE;

    // Ignore CHILD_SIG but not if it is SIGCHLD    
    if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD)
        if (signal(CHILD_SIG, SIG_IGN) == SIG_ERR)
            errExit("signal");
    
    // Create child; child commences execution in childFunc()
    if (clone(childFunc, stackTop, flags | CHILD_SIG, (void *) &fd) == -1)
        errExit("clone");
    // Parent falls through here. Wait for child;
    if (waitpid(-1, NULL, (CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1)
        errExit("waitpid");
    printf("child has terminated\n");

    s = write(fd, "x", 1);
    if (s == -1 && errno == EBADF)
        printf("file descriptor %d has been closed\n", fd);
    else if (s == -1)
        printf("write() on file descriptor %d failed unexpectedly (%s)\n", fd, strerror(errno));
    else
        printf("write() on file descriptor %d succeeded\n", fd);
    
    exit(EXIT_SUCCESS);
}
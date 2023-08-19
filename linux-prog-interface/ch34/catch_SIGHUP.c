// Catching SIGHUP

#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <signal.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void handler(int sig)
{

}

int main(int argc, char *argv[])
{
    pid_t childPid;
    struct sigaction sa;

    setbuf(stdout, NULL);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        errExit("sigaction");

    childPid = fork();
    if (childPid == -1)
        errExit("fork");

    // If a command line arg is supplied, move child process to a new process group
    // SIGHUP will not be sent to this new process group
    if (childPid == 0 && argc > 1)
        if (setpgid(0, 0) == -1)
            errExit("setpgid");
    
    printf("PID=%ld; PPID=%ld; PGID=%ld; SID=%ld\n", (long)getpid(), (long)getppid(), (long)getpgrp(), (long)getsid(0));

    // The process gets a SIGALRM in 60 seconds which ensures this process will die if nothing else terminates it
    alarm(60);

    // A infinite loop to wait for signal of SIGHUP, i.e. closing terminal window
    for (;;)
    {
        pause();
        printf("%ld: caght SIGHUP\n", (long)getpid());
    }
}
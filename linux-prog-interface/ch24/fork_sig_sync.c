// Using signals to synchronize process actions

#include <signal.h>
#include "../ch10/curr_time.h"
#include "../ch10/curr_time.c"
#include "tlpi_hdr.h"
#include "error_functions.c"

#define SYNC_SIG SIGUSR1

// Signal handler - does nothing but return
static void handler(int sig)
{

}

int main(int argc, char *argv[])
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    // Disable buffering of stdout
    setbuf(stdout, NULL);

    // Clear all signals from a set
    sigemptyset(&blockMask);
    // Add a signal to a set
    sigaddset(&blockMask, SYNC_SIG);
    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
        errExit("sigprocmask");
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if (sigaction(SYNC_SIG, &sa, NULL) == -1)
        errExit("sigaction");

    switch(childPid = fork())
    {
        case -1:
            errExit("fork");
        
        case 0:
            printf("[%s %ld] Child started - doing some work\n", currTime("%T"), (long)getpid());
            // do some work
            sleep(2);
            // signal parent that it is done
            printf("[%s %ld] Child about to signal parent\n", currTime("%T"), (long)getpid());
            if (kill(getppid(), SYNC_SIG) == -1)
                errExit("kill");

            // Child can do other things
            // and exit normally
            _exit(EXIT_SUCCESS);
        
        default:
            // Parent may do some work here and then waits for child to complete the required action
            printf("[%s %ld] Parent about to wait for signal\n", currTime("%T"), (long)getpid());
            sigemptyset(&emptyMask);
            if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
            
            printf("[%s %ld] Parent got signal\n", currTime("%T"), (long)getpid());
            if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
                errExit("sigprocmask");
            
            exit(EXIT_SUCCESS);
    }
}
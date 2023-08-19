// Implementation of system()

#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "../ch26/print_wait_status.c"

int system(const char *command)
{
    sigset_t blockMask, origMask;
    struct sigaction saIgnore, saOrigQuit, saOrigInt, saDefault;
    pid_t childPid;
    int status, savedErrno;

    // Check if a shell is available
    if (command == NULL)
        // ":" is a shell command that does nothing but return success status code
        return system(":") == 0;
    
    // Block signal SIGCHLD - empty blockMask and add SIGCHLD to it
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    // Set Block signals to those listed in blockMask, save previous SIG_BLOCK to origMask
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);

    // Set a signal actioner's signal handler to ignore
    saIgnore.sa_handler = SIG_IGN;
    saIgnore.sa_flags = 0;
    sigemptyset(&saIgnore.sa_mask);
    // Change action to signal SIGNIT to saIgnore, save original action to saOrigInt
    sigaction(SIGINT, &saIgnore, &saOrigInt);
    sigaction(SIGQUIT, &saIgnore, &saOrigQuit);

    switch (childPid = fork())
    {
        case -1:
            status = -1;
            break;
        
        case 0:
            saDefault.sa_handler = SIG_DFL;
            saDefault.sa_flags = 0;
            sigemptyset(&saDefault.sa_mask);
            
            if (saOrigInt.sa_handler != SIG_IGN)
                sigaction(SIGINT, &saDefault, NULL);
            if (saOrigQuit.sa_handler != SIG_IGN)
                sigaction(SIGQUIT, &saDefault, NULL);
            
            sigprocmask(SIG_SETMASK, &origMask, NULL);

            execl("/bin/sh", "sh", "-c", command, (char *)NULL);
            _exit(127);
        
        default:
            // On success, status of child will be returned
            while(waitpid(childPid, &status, 0) == -1)
            {
                // if waitpid() failed with errno == EINTR,i.e. interupted, restart the waitpid()
                if (errno != EINTR)
                {
                    status = -1;
                    break;
                }
            }
            break;
    }

    // The following may change errno
    savedErrno = errno;
    // Unblock SIGCHLD, restore the dispositions of SIGINT, and SIGQUIT
    sigprocmask(SIG_SETMASK, &origMask, NULL);
    sigaction(SIGINT, &saOrigInt, NULL);
    sigaction(SIGQUIT, &saOrigQuit, NULL);

    errno = savedErrno;

    return status;
}
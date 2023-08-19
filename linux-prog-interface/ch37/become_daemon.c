// Creating a daemon process

#include <sys/stat.h>
#include <fcntl.h>
#include "become_daemon.h"
#include "tlpi_hdr.h"

int becomeDaemon(int flags)
{
    int maxfd, fd;

    switch(fork())
    {
        case -1: return -1;
        // Child goes on from here
        case 0: break;
        // Parent terminates
        default: _exit(EXIT_SUCCESS);
    }

    // Child creates a new session and becomes its leader
    if (setsid() == -1)
        return -1;

    // A grandchild - in the newly created session but surely not session leader
    switch(fork())
    {
        case -1: return -1;
        // Grandchild goes on from here
        case 0: break;
        // Child terminates
        default: _exit(EXIT_SUCCESS);
    }

    if (!(flags & BD_NO_UMASK0))
        umask(0);

    if (!(flags & BD_NO_CHDIR))
        chdir("/");

    if (!(flags & BD_NO_CLOSE_FILES))
    {
        maxfd = sysconf(_SC_OPEN_MAX);
        if (maxfd == -1)
            maxfd = BD_MAX_CLOSE;
        
        // Close all fd
        for (fd = 0; fd < maxfd; fd++)
            close(fd);
    }

    if (!(flags & BD_NO_REOPEN_STD_FDS))
    {
        // Specifically close stdin, i.e. 0
        close(STDIN_FILENO);

        // Open /dev/null, the fd should be 0, i.e. the lowest available
        fd = open("/dev/null", O_RDWR);

        if (fd != STDIN_FILENO)
            return -1;
        
        // Close stdout and make stdout_fileno also /dev/null
        if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
            return -1;

        // Close stderr and make stderr also /dev/null
        if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
            return -1;
    }

    return 0;
}
// Creating a new session

#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    if (fork() != 0)
        _exit(EXIT_SUCCESS);

    // setsid() makes calling process the leader of a new session and is made the leader of a new process group
    // PID=PGID=SID
    if (setsid() == -1)
        errExit("setsid");

    printf("PID=%ld, PGID=%ld, SID=%ld\n", (long)getpid(), (long)getpgrp(), (long)getsid(0));

    // But calling process has no controlling terminal, i.e. /dev/tty
    if (open("/dev/tty", O_RDWR) == -1)
        errExit("open /dev/tty");
    
    exit(EXIT_SUCCESS);
}
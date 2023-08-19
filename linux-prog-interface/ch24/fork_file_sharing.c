// Sharing of file offset and open file status flags between parent and child

#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    // Disable buffering of stdout
    setbuf(stdout, NULL);

    fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");
    
    printf("File offset before fork(): %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl - F_GETFL");
    
    printf("O_APPEND flag before fork() is: %s\n", (flags & O_APPEND) ? "on" : "off");

    switch (fork())
    {
        case -1:
            errExit("fork");
        case 0:
            if (lseek(fd, 1000, SEEK_SET) == -1)
                errExit("lseek");

            // Fetch current flags
            flags = fcntl(fd, F_GETFL);
            if (flags == -1)
                errExit("fcntl - F_GETFL");

            // Turn on O_APPEND
            flags |= O_APPEND;
            if (fcntl(fd, F_SETFL, flags) == -1)
                errExit("fcntl - F_SETFL");
            // After fork(), only one of parent and child terminate by calling exit(); others should use _exit() 
            _exit(EXIT_SUCCESS);

        default:
            if (wait(NULL) == -1)
                // Wait for child to exit
                errExit("wait");
            printf("Child has exited\n");

            printf("File offset in parent: %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

            flags = fcntl(fd, F_GETFL);
            if (flags == -1)
                errExit("fcntl - F_GETFL");
            printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");

            exit(EXIT_SUCCESS);
    }
}
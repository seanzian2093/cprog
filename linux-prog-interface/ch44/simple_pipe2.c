// Using a pipe to communicate between a parent and child process

#include <sys/wait.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define BUF_SIZ 10

int main(int argc, char *argv[])
{
    int pfd[2];
    char buf[BUF_SIZ];
    ssize_t numRead;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s string\n", argv[0]);
    
    // Create a pipe
    if (pipe(pfd) == -1)
        errExit("pipe");
    
    switch(fork())
    {
        case -1:
            errExit("fork");
        
        // Child - reads from pipe
        case 0:
            // Close the write end fd
            if (close(pfd[1]) == -1)
                errExit("close - child");
            printf("Child - closed write end of pipe\n");
            
            for (;;)
            {
                numRead = read(pfd[0], buf, BUF_SIZ);
                // printf(" - Child - read %d bytes\n", (int)numRead);
                if (numRead == -1)
                    errExit("read");

                // If no bytes to read, e.g. EOF; end the loop
                if (numRead == 0)
                {
                    printf("\nChild - breaking loop\n");
                    break;
                }
                
                // Write bytes of numRead to stdout
                if (write(STDOUT_FILENO, buf, numRead) != numRead)
                    fatal("child- partial/failed write");
            }

            // Write a newline to stdout and exit 
            // write(STDOUT_FILENO, "\n", 1);
            printf("Child - exiting\n");
            if (write(STDOUT_FILENO, "\n", 1) != 1)
                errExit("write - newline");
            if (close(pfd[0]) == -1)
                errExit("close");
            // _exit(EXIT_SUCCESS);
            exit(EXIT_SUCCESS);

        // Parent - writes to pipe
        default:
            break;
    }
    // Close its read end fd
    if (close(pfd[0]) == -1)
        errExit("close - parent");
    
    // Write to write end fd
    if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
        fatal("parent - partial/failed write");
    
    // Close write end so that child will read EOF
    if (close(pfd[1]) == -1)
        errExit("close");
    
    printf("Parent- closed write end of pipe\n");
    // Wait for child to terminate
    wait(NULL);
    printf("Parent- doing some other work after child terminates.\n");
    exit(EXIT_SUCCESS);
}
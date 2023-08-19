// Using a pipe to connect ls and wc

#include <sys/wait.h>
#include "tlpi_hdr.h"
#include "error_functions.c"


int main(int argc, char *argv[])
{
    int pfd[2];

    if (pipe(pfd) == -1)
        errExit("pipe");

    // Create a child to exec ls
    switch(fork())
    {
        case -1:
            errExit("fork");
        
        // First child - exec `ls` to write to pipe
        case 0:
            // Close the read end fd
            if (close(pfd[0]) == -1)
                errExit("close 1");
            
            if (pfd[1] != STDOUT_FILENO)
            {
                // Duplicate a write end of pipe and assgin stdout fileno to it
                if (dup2(pfd[1], STDOUT_FILENO) == -1)
                    errExit("dup2 1");
                // Close duplicated write end fd
                if (close(pfd[1]) == -1)
                    errExit("close 2");
            }

            execlp("ls", "ls", (char *) NULL);
            errExit("execlp ls");
        
        // Parent falls through to create next child
        default:
            break;
    }
            
    // Create a child to exec wc
    switch(fork())
    {
        case -1:
            errExit("fork");
        
        // Second child - exec `wc` to read from pipe
        case 0:
            // Close the write end fd
            if (close(pfd[1]) == -1)
                errExit("close 3");
            
            if (pfd[0] != STDIN_FILENO)
            {
                // Duplicate a read end of pipe and assgin stdin fileno to it
                if (dup2(pfd[0], STDIN_FILENO) == -1)
                    errExit("dup2 2");
                // Close duplicated read end fd
                if (close(pfd[0]) == -1)
                    errExit("close 4");
            }

            execlp("wc", "wc", "-l", (char *) NULL);
            errExit("execlp wc");
        
        // Parent falls through 
        default:
            break;
    }

    if (close(pfd[0]) == -1)
        errExit("close 5");
    if (close(pfd[1]) == -1)
        errExit("close 6");

    if (wait(NULL) == -1)
        errExit("wait 1");
    if (wait(NULL) == -1)
        errExit("wait 2");
    
    exit(EXIT_SUCCESS);
}
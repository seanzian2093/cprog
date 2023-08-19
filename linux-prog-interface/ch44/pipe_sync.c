// Using a pipe to synchronize multiple processes

#include "../ch10/curr_time.c"
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

int main(int argc, char *argv[])
{
    int pfd[2];
    int j, dummy;


    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);
    
    setbuf(stdout, NULL);

    printf("%s Parent started\n", currTime("%T"));

    if (pipe(pfd) == -1)
        errExit("pipe");

    for (j = 1; j < argc; j++)
    {
        switch(fork())
        {
            case -1:
                errExit("fork");
        
            // Child - writes to pipe
            case 0:
                // Close the read end fd
                if (close(pfd[0] == -1))
                    errExit("close - child");
                // Child does some work 
                sleep(getInt(argv[j], GN_NONNEG, "sleep-time")); 
                printf("%s Child %d (PID=%ld) closing pipe\n", currTime("%T"), j, (long) getpid());

                // Close the write end fd
                if (close(pfd[1]) == -1)
                    errExit("close - child");
                
                _exit(EXIT_SUCCESS);
            
            // Parent loops to create next child
            default:
                break;
        }
    }
    // Parent closes the write end fd
    if (close(pfd[1]) == -1)
        errExit("close");
                
    if (read(pfd[0], &dummy, 1) != 0)
        fatal("parent did not get EOF");
    printf("%s Parent ready to go\n", currTime("%T"));

    exit(EXIT_SUCCESS);
}
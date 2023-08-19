// Creating a zombie child process
#include <signal.h>
// For basename() declaration
#include <libgen.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

#define CMD_SIZE 200

int main(int argc, char *argv[])
{
    char cmd[CMD_SIZE];
    pid_t childPid;

    // Always disable buffering of stdout when using fork() and printf() in one place
    setbuf(stdout, NULL);
    
    printf("Parent PID=%ld\n", (long) getpid());

    switch (childPid = fork())
    {
        case -1:
            errExit("fork");
        
        case 0:
            // Child immediately exits to become zombie
            printf("Child (PID=%ld) exiting\n", (long)getpid());
            _exit(EXIT_SUCCESS);
        
        default:
            // Give child a chance to start and exit
            sleep(3);
            snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
            cmd[CMD_SIZE - 1] = '\0';
            system(cmd);
        
            // Send sure-kill signal to the zombie
            if (kill(childPid, SIGKILL) == -1)
                errExit("kill");
            sleep(3);
            printf("After SIGKILL to zombie (PID=%ld):\n", (long)childPid);
            system(cmd);

            exit(EXIT_SUCCESS);
    }
}
// Establishing the same handler for two different signals
#include <signal.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void sigHandler(int sig)
{
    static int count = 0;
    if (sig == SIGINT)
    {
        count++;
        printf("Caught SIGINT (%d)\n", count);
        // Resume execution at the point of interruption
        return;
    }
    printf("Caught SIGQUIT - that's all folks!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("signal");

    if (signal(SIGQUIT, sigHandler) == SIG_ERR)
        errExit("signal");

    // Loop forever, waiting for signals
    for (;;)
        // Block untill a signal is caught
        pause();
}
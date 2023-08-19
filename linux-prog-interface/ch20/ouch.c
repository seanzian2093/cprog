// Installing a handler for SIGINT
#include <signal.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void sigHandler(int sig)
{
    printf("Ouch!\n");
}

int main(int argc, char *argv[])
{
    int j;

    if (signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("signal");

    for (j = 0; ; j++)
    {
        printf("%d\n", j);
        sleep(3);
    }
}
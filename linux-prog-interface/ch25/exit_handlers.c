// Using exit handlers
// Get on_exit() declaration from stdlib.h
// _BSD_SOURCE and _SVID_SOURCE are depreciated.
// #define _BSD_SOURCE
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void atexitFunc1(void)
{
    printf("atexit function 1 called\n");
}

static void atexitFunc2(void)
{
    printf("atexit function 2 called\n");
}

static void onexitFunc(int exitStatus, void *arg)
{
    printf("on_exit function called; status=%d, arg=%ld\n", exitStatus, (long)arg);
}

int main(int argc, char *argv[])
{
    if (on_exit(onexitFunc, (void *) 10) != 0)
        fatal("on_exit 1");

    if (atexit(atexitFunc1) != 0)
        fatal("atexit 1");

    if (atexit(atexitFunc2) != 0)
        fatal("atexit 2");

    if (on_exit(onexitFunc, (void *) 20) != 0)
        fatal("on_exit 2");

    // status passed to exit() is also passed to on_exit()'s 1st arg func, as its 1st arg
    exit(2);
}

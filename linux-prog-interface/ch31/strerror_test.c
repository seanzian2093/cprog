// Calling strerror() from two different threads
#include <stdio.h>
#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "strerror.c"

static void *threadFunc(void *arg)
{
    char *str;
    printf("Other thread about to call strerror()\n");
    str = strerror0(1);
    printf("Other thread: str (%p) = %s\n", str, str);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t;
    int s;
    char *str;

    str = strerror0(2);
    printf("Main thread has called strerror()\n");

    s = pthread_create(&t, NULL, threadFunc, NULL);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    // str will be overwritten by other thread
    printf("Main thread: str (%p) = %s\n", str, str);

    exit(EXIT_SUCCESS);
}
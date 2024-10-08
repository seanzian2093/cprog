// A simple program using Pthreads

#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void *threadFunc(void *arg)
{
    char *s = (char *) arg;
    printf("%s", s);
    return (void *) strlen(s);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello World\n");

    if (s != 0)
        errExitEN(s, "pthread_create");

    // order of this message and the one from thread t1, is indeterminate
    printf("Message from main()\n");
    // Wait on thread with thread ID t1 to terminate and store its return value to res if not NULL
    s = pthread_join(t1, &res);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("Thread returned %ld\n", (long)res);

    exit(EXIT_SUCCESS);
}
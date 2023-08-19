// Using a mutex to protect access to a global variable
// call with ./thread_incr 1000, result is determinate

#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

static int glob = 0;
// PTHREAD_MUTEX_INITIALIZER can only be used to declare static mutex
// Use pthread_mutex_init() to dynamically initialize mutex
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void * threadFunc(void *arg)
{
    int loops = *((int *) arg);
    // loc is an automatic varialbe allocated on the per-thread stack, i.e. each thread has its own copy of loc
    int loc, j, s;

    for (j = 0; j < loops; j++)
    {
        // Lock the mutex and modify global variable
        s = pthread_mutex_lock(&mtx);
        if (s != 0)
            errExitEN(s, "pthread_mutex_lock");
        loc = glob;
        loc ++;
        glob = loc;

        // Job is done; unlock the mutex
        s = pthread_mutex_unlock(&mtx);
        if (s != 0)
            errExitEN(s, "pthread_mutex_unlock");
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 1000000;

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}
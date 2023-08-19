// Using cleanup handlers

#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int glob = 0;

static void cleanupHandler(void *arg)
{
    int s;
    printf("cleanup: freeing block at %p\n", arg);
    free(arg);

    printf("cleanup: unlocking mutex\n");
    s = pthread_mutex_unlock(&mtx);
    if (s != 0)
        errExitEN(s, "pthread_mutex_unlock");
}

static void *threadFunc(void *arg)
{
    int s;
    void *buf = NULL;

    buf = malloc(0x10000);
    printf("thread: aloocated memory at %p\n", buf);

    // When a new thread starts
    // lock the mtx
    s = pthread_mutex_lock(&mtx);
    if (s != 0)
        errExitEN(s, "pthread_mutex_lock");

    // Install a cleanup function
    pthread_cleanup_push(cleanupHandler, buf);

    // Do some work but with cancellation points
    while(glob == 0)
    {
        // Wait for cond to be signaled; a cancellation point
        s = pthread_cond_wait(&cond, &mtx);
        if (s != 0)
            errExitEN(s, "pthread_cond_wait");
    }

    // Done the work
    printf("thread: condition wait loop completed\n");
    // Execute cleanup function
    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thr;
    void *res;
    int s;

    s = pthread_create(&thr, NULL, threadFunc, NULL);
    if (s != 0)
        errExitEN(s, "pthread_create");
    
    sleep(2);

    if (argc == 1)
    {
        printf("main: about to cancel thread\n");
        // pthread_cond_wait() is the only cancellation point
        s = pthread_cancel(thr);
        if (s != 0)
            errExitEN(s, "pthread_cancel");
    }
    else
    {
        // Signal the cond varialbe to let thread finish the work
        // So no cancellation point left
        printf("main: about to signal condition variable\n");
        glob = 1;
        s = pthread_cond_signal(&cond);
        if (s != 0)
            errExitEN(s, "pthread_cond_signal");
    }

    // Wait for a thread to terminated and save its exit status to res
    s = pthread_join(thr, &res);
    if (s != 0)
        errExitEN(s, "pthread_join");

    if (res == PTHREAD_CANCELED)
        printf("main: thread was canceled\n");
    else
        printf("main: thread terminated normally\n");

    exit(EXIT_SUCCESS);
}
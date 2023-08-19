// Cancelling a thread with pthread_cancel()

#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

static void *threadFunc(void *arg)
{
    int j;
    printf("New thread started\n");
    for (j = 1; ; j++)
    {
        // printf() may be a cancellation point
        printf("Loop %d\n", j);
        // sleep() is a cancellation point
        sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thr;
    int s;
    void *res;

    // Create a new thread
    s = pthread_create(&thr, NULL, threadFunc, NULL);
    if (s != 0)
        errExitEN(s, "pthread_create");

    // Allow new thread to run a while
    sleep(3);

    // Cancel it but not guaranteed that it terminates immediately
    // The thread accepts the cancellation request because it contains cancellation point
    // Use pthread_testcancel() periodically to repsond in a timely fashion to a cancellation request sent by another thread
    s = pthread_cancel(thr);
    if (s != 0)
        errExitEN(s, "pthread_cancel");

    // Join it - wait for thr to terminate and save its exit status to res
    s = pthread_join(thr, &res);
    if (s != 0)
        errExitEN(s, "pthread_join");

    if (res == PTHREAD_CANCELED)
        printf("Thread was canceled\n");
    else
        printf("Thread was not canceled(should not happen)\n");

    exit(EXIT_SUCCESS);
}
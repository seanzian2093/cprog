// A main thread that can join with any terminated thread
// ./thread_multjoin 1 1 2 3 4 5

#include <pthread.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totThreads = 0;
static int numLive = 0;
static int numUnjoined = 0;

enum tstate {
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};

static struct {
    pthread_t tid;
    enum tstate state;
    int sleepTime;
} * thread;

static void * threadFunc(void *arg)
{
    int idx = (int) arg;
    int s;
    sleep(thread[idx].sleepTime);
    printf("Thread %d terminating\n", idx);

    // Lock mutex and update critical global variables
    s = pthread_mutex_lock(&threadMutex);
    if (s != 0)
        errExitEN(s, "pthread_mutex_lock");

    numUnjoined++;
    thread[idx].state = TS_TERMINATED;

    // Updating is done; unlock the mutex
    s = pthread_mutex_unlock(&threadMutex);
    if (s != 0)
        errExitEN(s, "pthread_mutex_unlock");

    // Send singal to condition variable threadDied
    s = pthread_cond_signal(&threadDied);
    if (s != 0)
        errExitEN(s, "pthread_cond_signal");

    return NULL;
}

int main(int argc, char *argv[])
{
    int s, idx;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s nsecs...\n", argv[0]);

    thread = calloc(argc -1, sizeof(*thread));
    if (thread == NULL)
        errExit("calloc");
    
    for (idx = 0; idx < argc - 1; idx++)
    {
        thread[idx].sleepTime = getInt(argv[idx + 1], GN_NONNEG, NULL);
        thread[idx].state = TS_ALIVE;
        s = pthread_create(&thread[idx].tid, NULL, threadFunc, (void *) idx);/*segmentation fault*/
        if (s != 0)
            errExit("pthread_create");
    }

    totThreads = argc - 1;
    numLive = totThreads;

    while (numLive > 0)
    {
        // Lock mutex and update critical global variables
        s = pthread_mutex_lock(&threadMutex);
        if (s != 0)
            errExitEN(s, "pthread_mutex_lock");

        // When numLive > 0 and unUnjoined == 0, wait on signals sent to condition variable and blocking
        while (numUnjoined == 0)
        {
            s = pthread_cond_wait(&threadDied, &threadMutex);
            if (s != 0)
                errExitEN(s, "pthread_cond_wait");
        }

        // When unmUnjoined > 0; loop over all thread, search for terminated thread and join them
        for (idx = 0; idx < totThreads; idx++)
        {
            if (thread[idx].state == TS_TERMINATED)
            {
                s = pthread_join(thread[idx].tid, NULL);
                printf("Reaping thread %d - %ld, state=%d\n", idx, (long int) thread[idx].tid, (int) thread[idx].state);
                if (s != 0)
                    errExitEN(s, "pthread_join");

                // Update the thread state to joined
                thread[idx].state = TS_JOINED;
                // Update numLive and numUnjoined
                numLive--;
                numUnjoined--;

                printf("Reaped thread %d - %ld, state=%d (numLive=%d)\n\n", idx, (long int) thread[idx].tid, (int) thread[idx].state, numLive);
            }
        }

        // Updating is done; unlock the mutex
        s = pthread_mutex_unlock(&threadMutex);
        if (s != 0)
            errExitEN(s, "pthread_mutex_unlock");
    }

    exit(EXIT_SUCCESS);
}
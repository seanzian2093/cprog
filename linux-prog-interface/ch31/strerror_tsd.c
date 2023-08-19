// An implementation of strerror() using thread-specific data

// Not able to get _sys_nerr and _sys_errlist declaration from <stdio.h> since they are depreciated
// #define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include "tlpi_hdr.h"

static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t strerrorKey;

#define MAX_ERROR_LEN 256

static void destructor(void *buf)
{
    free(buf);
}

static void createKey(void)
{
    int s;
    // Allocate a unique thread-specific data key and record the address of the destructor 
    // The destructor will be used to free thread-specific data buffers
    s = pthread_key_create(&strerrorKey, destructor);
    if (s != 0)
        errExitEN(s, "pthread_key_create");
}

// Self-define _sys_errlist and _sys_nerr
const char *const _sys_errlist[] =
  {
    "Error 0",                        /* 0 */
    "Argument out of function's domain", /* 1 = EDOM */
    "Result out of range",        /* 2 = ERANGE */
    "Operation not implemented", /* 3 = ENOSYS */
    "Invalid argument",                /* 4 = EINVAL */
    "Illegal seek",                /* 5 = ESPIPE */
    "Bad file descriptor",        /* 6 = EBADF */
    "Cannot allocate memory",        /* 7 = ENOMEM */
    "Permission denied",        /* 8 = EACCES */
    "Too many open files in system", /* 9 = ENFILE */
    "Too many open files",        /* 10 = EMFILE */
  };

const int _sys_nerr = 10;

char *strerror0(int err)
{
    int s;
    char *buf;

    // pthread_once() sets up a mechanism that ensures that 1st invocation of strerror0() from any thread calls createKey()
    s = pthread_once(&once, createKey);
    if (s != 0)
        errExitEN(s, "pthread_once");
    
    buf = pthread_getspecific(strerrorKey);
    // If first call from this thread, allocate buffer for thread and save its location
    if (buf == NULL)
    {
        buf = malloc(MAX_ERROR_LEN);
        if (buf == NULL)
            errExit("malloc");
        
        s = pthread_setspecific(strerrorKey, buf);
        if (s != 0)
            errExitEN(s, "pthread_setspecific");
    }

    if (err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL)
    {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    }
    else
    {
        strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0';
    }

    return buf;
}
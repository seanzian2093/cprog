// An implementation of strerror() that is not thread-safe

// Not able to get _sys_nerr and _sys_errlist declaration from <stdio.h> since they are depreciated
// #define _GNU_SOURCE
#include <stdio.h>

#define MAX_ERROR_LEN 256

static char buf[MAX_ERROR_LEN];

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
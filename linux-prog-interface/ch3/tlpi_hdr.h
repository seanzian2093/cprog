// Header file used by most example programs
#ifndef TLPI_HDR_H
// Prevent accidental double inclusion
#define TLPI_HDR_H 

#include <sys/types.h>
#include <stdio.h>
// Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants
#include <stdlib.h>
// Prototypes for many system calls
#include <unistd.h>
// Declare errno and defines error constants
#include <errno.h>
// Commonly used string-handling functions
#include <string.h>
// Declare our functions for handling numeric arguments, getInt(), getLong()
#include "get_num.h"
// Declare our error-handling functions
#include "error_functions.h"
typedef enum { FALSE, TRUE } Boolean;
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif

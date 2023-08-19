// Copy input to output using system call- read and write
// #include "syscall.h"
// #include <syscall.h>
// #define BUFSIZ 1000
// #include "unistd.h"

// For system calls should use unistd.h instead of syscall.h
#include <unistd.h>
// BUFSIZ is defined in stdio.h
#include <stdio.h>

int main(void)
{
    char buf[BUFSIZ];
    int n;

    // read() return bytes read and 0 implies end of file, -1 error
    // read from file 0, i.e., stdin and store to buf, read BUFSIZ bytes if possible
    while ((n = read(0, buf, BUFSIZ)) > 0)
        // write n bytes to file 1, i.e. stdout from buf
        write(1, buf, n);
}
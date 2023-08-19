// Copy f1 to f2 using system calls

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#define PERMS 0666

void error(char *, ...);

int main(int argc, char *argv[])
{
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3)
        error("Usage: cp from to");
    
    // open and create return -1 if error
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        error("cp: can't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) == -1)
        error("cp: can't create %s, mode %03o", argv[2], PERMS);

    // read() return bytes read, 0 if end of file, -1 if error
    while ((n = read(f1, buf, BUFSIZ)) > 0)
    {
        // write() return bytes written always, not if error
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    }
    return 0;
}

// Print an error message and die
void error(char *fmt, ...)
{
    va_list args;
    
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    // vprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
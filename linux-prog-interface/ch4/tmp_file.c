// Demostration of read(), write() and lseek()

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

int main(void)
{
    int fd;
    char template[] = "/tmp/somestringXXXXXX";

    fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");
    printf("Generated file name was: %s\n", template);

    // Name disapperas immediately but the file is removed only after close()
    unlink(template);

    if (close(fd) == -1)
        errExit("close");
}
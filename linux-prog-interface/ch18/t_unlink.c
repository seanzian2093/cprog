// Removing a link with unlink()

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

#define CMD_SIZE 200
#define BUF_SIZ 1024

int main(int argc, char *argv[])
{
    int fd, j, numBlocks;
    // Command to be passed to system()
    char shellCmd[CMD_SIZE];
    // Random bytes to write to file
    char buf[BUF_SIZ];

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks] \n", argv[0]);
    
    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks") : 100000;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    
    // Remove filename but the file is still open
    if (unlink(argv[1]) == -1)
        errExit("unlink");

    for (j = 0; j < numBlocks; j++)
        if (write(fd, buf, BUF_SIZ) != BUF_SIZ)
            fatal("partial/failed write");
    
    // Redirect the output of printf() onto a buff, with max written
    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shellCmd);

    if (close(fd) == -1)
        errExit("close");

    printf("********* Closed file descriptor\n");

    system(shellCmd);

    exit(EXIT_SUCCESS);
}
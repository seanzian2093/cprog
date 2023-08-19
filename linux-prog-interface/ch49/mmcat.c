// Using mmap() to create a private file mapping
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    char *addr;
    int fd;
    struct stat sb;

    if (argc <2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    // Get size info the the file specified by fd, save to &sb
    if (fstat(fd, &sb) == -1)
        errExit("fstat");

    // Content of file fd was mapped into address space of this process
    // offset=0 causes file being mapped from beginning
    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    
    // write sb.st_size bytes from addr to stdout
    if (write(STDOUT_FILENO, addr, sb.st_size) != sb.st_size)
        fatal("partial/failed write");
    
    exit(EXIT_SUCCESS);
}

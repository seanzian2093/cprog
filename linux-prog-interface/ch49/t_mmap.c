// Using mmap() to create a shared file mapping

#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define MEM_SIZE 10

int main(int argc, char *argv[])
{
    char *addr;
    int fd;

    if (argc <2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);
    
    fd = open(argv[1], O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    
    // No longer need fd
    if (close(fd) == -1)
        errExit("close");

    printf("Current string=%.*s\n", MEM_SIZE, addr);

    if (argc > 2)
    {
        if (strlen(argv[2]) >= MEM_SIZE)
            cmdLineErr("'new-value' too larg\n");

        // Set entire memory region pointed to by addr to 0
        memset(addr, 0, MEM_SIZE);
        strncpy(addr, argv[2], MEM_SIZE - 1);
        // msync() makes sure contents of shared file mapping are written to underlying file
        if (msync(addr, MEM_SIZE, MS_SYNC) == -1)
            errExit("msync");
        
        printf("Copied \"%s\" to shared memory\n", argv[2]);
    }

    exit(EXIT_SUCCESS);
}
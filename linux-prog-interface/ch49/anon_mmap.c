// Sharing an anonymous mapping between parent and child process
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include "error_functions.c"


int main(int argc, char *argv[])
{
    char *addr;
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    // Initialize integer in mapped region
    *addr = 1;

    switch(fork())
    {
        case -1:
            errExit("fork");
        
        case 0:
            printf("Child started, value = %d\n", *addr);
            (*addr)++;
            if (munmap(addr, sizeof(int)) == -1)
                errExit("munmap");
            exit(EXIT_SUCCESS);
        
        default:
            if (wait(NULL) == -1)
                errExit("wait");
            printf("In parent, value = %d\n", *addr);
            if (munmap(addr, sizeof(int)) == -1)
                errExit("munmap");
            exit(EXIT_SUCCESS);
    }
}
// Changing memory protection with mprotect()

#include <sys/mman.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define LEN (1024 * 1024)
#define SHELL_FMT "cat /proc/%ld/maps | grep zero"
#define CMD_SIZE (sizeof(SHELL_FMT) + 20)

int main(int argc, char *argv[])
{
    char cmd[CMD_SIZE];
    char *addr;

    // Create an anonymous mapping with all access denied
    addr = mmap(NULL, LEN, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    printf("Before mprotect()\n");
    snprintf(cmd, CMD_SIZE, SHELL_FMT, (long)getpid());
    system(cmd);

    // Call mprotect() to change protections
    if (mprotect(addr, LEN, PROT_READ | PROT_WRITE) == -1)
        errExit("mprotect");
    
    printf("After mprotect()\n");
    system(cmd);

    exit(EXIT_SUCCESS);
}
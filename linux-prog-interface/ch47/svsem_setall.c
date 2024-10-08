// A semaphore monitoring program
#include <sys/types.h>
#include <sys/sem.h>
#include "semun.h"
#include "tlpi_hdr.h"
#include "get_num.c"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    struct semid_ds ds;
    union semun arg;
    int j, semid;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s semid val...\n", argv[0]);
    
    semid = getInt(argv[1], 0, "semid");

    arg.buf = &ds;
    if (semctl(semid, 0, IPC_STAT, arg) == -1)
        errExit("semctl");
    
    if (ds.sem_nsems != argc - 2)
        cmdLineErr("Set contains %ld semaphores, but %ld values were supplied\n", (long)ds.sem_nsems, argc - 2);

    arg.array = calloc(ds.sem_nsems, sizeof(arg.array[0]));
    if (arg.array == NULL)
        errExit("calloc");

    for (j = 2; j < argc; j++)
        arg.array[j - 2] = getInt(argv[j], 0, "val");

    // SETALL initializeds all semaphores in the set specified by semid, using values in arg.array
    if (semctl(semid, 0, SETALL, arg) == -1)
        errExit("semctl-SETALL");
    printf("Semaphore values changed (PID=%ld)\n", (long)getpid());
    
    exit(EXIT_SUCCESS);
}
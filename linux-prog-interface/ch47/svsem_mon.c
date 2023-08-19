// A semaphore monitoring program
#include <sys/types.h>
#include <sys/sem.h>
#include <time.h>
#include "../ch10/curr_time.c"
#include "semun.h"
#include "tlpi_hdr.h"
#include "get_num.c"
#include "error_functions.c"

int main( int argc, char *argv[])
{
    struct semid_ds ds;
    union semun arg, dummy;
    int semid, j;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s semid\n", argv[0]);
    
    semid = getInt(argv[1], 0, "semid");

    arg.buf = &ds;
    // IPC_STAT places a copy of semid_ds associated with the semaphore specified by semid, in the buffer pointed to by arg.buf
    if (semctl(semid, 0, IPC_STAT, arg) == -1)
        errExit("semctl");
    
    printf("Semaphore changed: %s", ctime(&ds.sem_ctime));
    printf("Last semop():      %s", ctime(&ds.sem_otime));

    // ds.sem_nsems is initialized to the number of semaphores in the set
    arg.array = calloc(ds.sem_nsems, sizeof(arg.array[0]));
    if (arg.array == NULL)
        errExit("calloc");

    // Get all values semephore of the set specified by semid and place them in the array pointed to by arg.array
    if (semctl(semid, 0, GETALL, arg) == -1)
        errExit("semctl-GETALL");
    
    printf("Sem # Value SEMPID  SEMNCNT SEMZCNT\n");

    for (j = 0; j < ds.sem_nsems; j++)
        printf("%3d %5d %5d %5d %5d\n", j, arg.array[j], 
                // Get process ID of the last process which performed semop() on this semaphore, specified by j
                semctl(semid, j, GETPID, dummy),
                // Get number of processes that are wait for the semaphore to increase
                semctl(semid, j, GETNCNT, dummy),
                // Get number of processes that are wait for the semaphore to become 0
                semctl(semid, j, GETZCNT, dummy));
    
    exit(EXIT_SUCCESS);
}
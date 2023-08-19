// Transfer blocks of data from a shared memory segment to stdout

#include "svshm_xfr.h"
#include "error_functions.c"
#include "../ch47/binary_sems.c"

int main(int argc, char *argv[])
{
    int semid, shmid, bytes, xfrs;
    struct shmseg *shmp;

    // Get semephore set id
    semid = semget(SEM_KEY, 0, 0);
    if (semid == -1)
        errExit("semget");
    
    // Get shared memory segment id
    shmid = shmget(SHM_KEY, 0, 0);
    if (shmid == -1)
        errExit("shmget");

    // Attach it to read(this main()) virtual address space at an address chose by kernel(shmaddr = NULL), in read-only mode
    shmp = shmat(shmid, NULL, SHM_RDONLY);
    if (shmp == (void *) -1)
        errExit("shmat");

    // Transfer data from shared memory to stdout
    for (xfrs = 0, bytes = 0; ;xfrs++)
    {
        // Wait on semaphore, i.e., reserve it
        if (reserveSem(semid, READ_SEM) == -1)
            errExit("reserveSem");

        // Reached EOF
        if (shmp->cnt == 0)
            break;
        bytes += shmp->cnt;
        
        if(write(STDOUT_FILENO, shmp->buf, shmp->cnt) != shmp->cnt)
            fatal("partial/failed write");
        
        // Release the semephore so that the writer program can use it
        if (releaseSem(semid, WRITE_SEM) == -1)
            errExit("releaseSem");

    }

    if (shmdt(shmp) == -1)
        errExit("shmdt");
        
    // Give writer one more tur so it can clean up
    if (releaseSem(semid, WRITE_SEM) == -1)
        errExit("releaseSem");
    
    fprintf(stderr, "Received %d bytes (%d xfrs)\n", bytes, xfrs);
    exit(EXIT_SUCCESS);
}

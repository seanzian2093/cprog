// Transfer blocks of data from stdin to a shared memory segment

#include "../ch47/semun.h"
#include "svshm_xfr.h"
#include "error_functions.c"
#include "../ch47/binary_sems.c"

int main(int argc, char *argv[])
{
    int semid, shmid, bytes, xfrs;
    struct shmseg *shmp;
    union semun dummy;

    // Create 2 semaphores to be used by writer and reader program
    semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
    if (semid == -1)
        errExit("semget");
    // Initialize first semaphore to available
    if (initSemAvailable(semid, WRITE_SEM) == -1)
        errExit("initSemAvailable");
    // Initialize second semaphore to in use
    if (initSemInUse(semid, READ_SEM) == -1)
        errExit("initSemInUse");
    
    // Create a shared memory segment
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | OBJ_PERMS);
    if (shmid == -1)
        errExit("shmget");

    // Attach it to writer(this main()) virtual address space at an address chose by kernel(shmaddr = NULL)
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *) -1)
        errExit("shmat");

    for (xfrs = 0, bytes = 0; ;xfrs++, bytes += shmp->cnt)
    {
        // Wait on semaphore, i.e., reserve it
        if (reserveSem(semid, WRITE_SEM) == -1)
            errExit("reserveSem");
        
        shmp->cnt = read(STDIN_FILENO, shmp->buf, BUF_SIZE);
        if (shmp->cnt == -1)
            errExit("reserveSem");
        
        // Release the semephore so that the reader program can use it
        if (releaseSem(semid, READ_SEM) == -1)
            errExit("releaseSem");

        // Reached EOF
        if (shmp->cnt == 0)
            break;
    }
        
    // Wait untill reader has let us have one more turn. We then know reader has finished and so we can delete IPC objects.
    if (reserveSem(semid, WRITE_SEM) == -1)
        errExit("reserveSem");
    
    // Remove semephore set
    if (semctl(semid, 0, IPC_RMID, dummy) == -1)
        errExit("semctl");
    // Detach shared memory segment
    if (shmdt(shmp) == -1)
        errExit("shmdt");
    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, 0) == -1)
        errExit("shmctl");
    
    fprintf(stderr, "Sent %d bytes (%d xfrs)\n", bytes, xfrs);
    exit(EXIT_SUCCESS);
}
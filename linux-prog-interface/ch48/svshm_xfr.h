// Header file for svshm_xfr_writer.c and svshm_xfr_reader.c

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "tlpi_hdr.h"
#include "../ch47/binary_sems.h"

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678

// Permissions for IPC object
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

// Writer has access to shared memory
#define WRITE_SEM 0
// Reader has access to shared memory
#define READ_SEM 1

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

// Define structure of shared memory segment
struct shmseg
{
    int cnt;
    char buf[BUF_SIZE];
};
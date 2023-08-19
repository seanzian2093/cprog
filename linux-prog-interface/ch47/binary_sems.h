// Header file for binary_sems.c
#ifndef BINARY_SEMS_H
#define BINARY_SEMS_H

#include "tlpi_hdr.h"

// Use SEM_UNDO during semop()?
extern Boolean bsUseSemUndo;
// Retry if semop() is interrupted by signal handler?
extern Boolean bsRetryOnEintr;

int initSemAvailable(int semId, int semNum);
int initSemInUse(int semId, int semNum);
int reserveSem(int semId, int semNum);
int releaseSem(int semId, int semNum);
#endif
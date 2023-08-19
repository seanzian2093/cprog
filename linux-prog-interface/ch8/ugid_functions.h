// Header file for ugid_functions.c

// sudo ln -s -f $(pwd)/ugid_functions.h /usr/include

#ifndef UGID_FUNCTIONS_H
#define UGID_FUNCTIONS_H

#include "tlpi_hdr.h"

char * userNameFromId(uid_t uid);
uid_t userIdFromName(const char *name);
char *groupNameFromId(gid_t gid);
gid_t groupIdFromName(const char *name);

#endif
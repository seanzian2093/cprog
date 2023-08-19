// Functions to convert user and group IDs to and from user and group names

#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "ugid_functions.h"

// Return name corresponding to uid or NULL on error
char *userNameFromId(uid_t uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

// Return uid corresponding to name or -1 on error
uid_t userIdFromName(const char *name)
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;

    // Return -1 on emtpy string or NULL
    if (name == NULL || *name == '\0')
        return -1;
    
    // If caller provides a numeric string, return it
    u = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return u;

    pwd = getpwnam(name);
    if (pwd == NULL)
        return -1;
    
    return pwd->pw_uid;
}

// Return name corresponding to gid or NULL on error
char *groupNameFromId(gid_t gid)
{
    struct group *grp;
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

// Return gid corresponding to name or -1 on error
gid_t groupIdFromName(const char *name)
{
    struct group *grp;
    gid_t g;
    char *endptr;

    // Return -1 on emtpy string or NULL
    if (name == NULL || *name == '\0')
        return -1;
    
    // If caller provides a numeric string, return it
    g = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return g;

    grp = getgrnam(name);
    if (grp == NULL)
        return -1;
    
    return grp->gr_gid;
}
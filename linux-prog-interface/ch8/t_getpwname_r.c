
// Demonstrate the use of getpwname() to retrieve the password record from passwd file for a named user
#include <pwd.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s username\n", argv[0]);
    
    size_t bufSize = sysconf(_SC_GETPW_R_SIZE_MAX);

    char *buf = malloc(bufSize);
    if (buf == NULL)
        errExit("malloc %d\n", bufSize);

    struct passwd *result;
    struct passwd pwd;

    int s = getpwnam_r(argv[1], &pwd, buf, bufSize, &result);

    if (s != 0)
        errExitEN(s, "getpwname_r");
    
    if (result != NULL)
        printf("Name: %s\n", pwd.pw_gecos);
    else
        printf("Not found\n");
    
    printf("result points to: %p\n", result);
    printf("pwd is stored at: %p\n", &pwd);
    
    exit(EXIT_SUCCESS);
}
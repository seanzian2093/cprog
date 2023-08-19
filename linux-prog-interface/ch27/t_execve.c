// Using execve() to execute a new program

#include "tlpi_hdr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    char *argVec[10];
    char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);
    
    // strrchr() returns last '/' in argv[1], or NULL if not present;
    // i.e. get basename from argv[1]
    argVec[0] = strrchr(argv[1], '/');
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argVec[1];
    argVec[1] = "hello world";
    argVec[2] = "good bye";
    // List must be null-terminated 
    argVec[3] = NULL;

    execve(argv[1], argVec, envVec);
    // If we get here, something went wrong
    errExit("execve");
}
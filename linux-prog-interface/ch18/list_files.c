// Scanning a directory

#include <dirent.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

// List all files in 'dirPath'
static void listFiles(const char *dirPath)
{
    DIR *dirp;
    struct dirent *dp;
    // True if 'dirPath' is "."
    Boolean isCurrent;

    isCurrent = strcmp(dirPath, ".") == 0;

    dirp = opendir(dirPath);
    if (dirp == NULL)
    {
        errMsg("opendir failed on '%s'", dirPath);
        return;
    }

    // For each entry in this directory, print directory + filename
    for (;;)
    {
        // To distinguish error from end-of-directory
        errno = 0;
        dp = readdir(dirp);
        if(dp == NULL)
            break;
        
        // Skip two entries: . and ..
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        // if in pwd, print file name only
        if (!isCurrent)
            printf("%s/", dirPath);
        printf("%s\n", dp->d_name);
    }

    if (errno != 0)
        errExit("readdir");

    if (closedir(dirp) == -1)
        errExit("closedir");
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [dir...]\n", argv[0]);

    if (argc == 1)
        listFiles(".");
    else
        for (argv++; *argv; argv++)
            listFiles(*argv);

    exit(EXIT_SUCCESS);
}
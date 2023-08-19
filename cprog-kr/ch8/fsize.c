// This is the 2nd part - fsize

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"

void fsize(char *);

int main(int argc, char **argv)
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

// int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn) (char *));

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        // Apply fsize to each file in the directory
        dirwalk(name, fsize);
    printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024
// Apply fcn to all files in dir
void dirwalk(char *dir, void (*fcn) (char *))
{
    char name[MAX_PATH];
    Dirent0 *dp;
    DIR0 *dfd;

    // opendir() takes a string of filename, returns a DIR or NULL if error
    if ((dfd = opendir0(dir)) == NULL) 
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    // readdir() takes a DIR and returns a pointer to info for the next file or NULL when no file left
    while ((dp = readdir0(dfd)) != NULL)
    {
        // Skip self and parent dir otherwise infinite loop
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
            continue;
        
        if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        else 
        {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir0(dfd);
}

int fstat(int fd, struct stat *);

// Open a directory for readdir calls
DIR0 *opendir0(char *dirname)
{
    int fd;
    struct stat stbuf;
    DIR0 *dp;
    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR0 *) malloc(sizeof(DIR0))) == NULL)
        return NULL;
    
    dp->fd = fd;
    return dp;
}

// Close directory and free space
void closedir0(DIR0 *dp)
{
    if (dp)
    {
        close(dp->fd);
        free(dp);
    }
}

#include <sys/dir.h>
// Read directory entries in sequence
Dirent0 *readdir0(DIR0 *dp)
{
    // Local directory structure
    struct direct dirbuf;
    // Previously defined portable structure
    static Dirent0 d;

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
    {
        if (dirbuf.d_ino == 0)
            continue;
        d.ino = dirbuf.d_ino;
        // strncpy(d.name, dirbuf.d_name, DIRSIZ);
        strncpy(d.name, dirbuf.d_name, NAME_MAX);
        // d.name[DIRSIZ] = '\0';
        d.name[NAME_MAX] = '\0';
        return &d;
    }
    return NULL;
}
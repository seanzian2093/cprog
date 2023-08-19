// Print the sizes of all files named in its command line argument list.
// If one of the files is a directory, fsize applies itself recursively to that directory.
// If no argument at all, it processes the current directory.


// Divide this programm to 2 piecies - directory entry and file size. This is directory entry part.

// Longest filename component, system-dependent
#define NAME_MAX 14

// Define a new type for a portable directory entry - inode number and filename
typedef struct {
    long ino;
    char name[NAME_MAX+1];
} Dirent0;

// Define a DIR struct to which opendir returns a pointer to 
typedef struct {
    // file descriptor for the directory
    int fd;
    // the directory itself
    Dirent0 d;
} DIR0;

DIR0 *opendir0(char *dirname);
Dirent0 *readdir0(DIR0 *dfd);
void closedir0(DIR0 *dfd);
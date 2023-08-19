// Demostration of read(), write() and lseek()

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

int main(int argc, char *argv[])
{
    // Use special types for special purposes
    size_t len;
    off_t offset;
    ssize_t numRead, numWritten;

    int fd, ap, j;
    char *buf;

    if (argc <3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
    
    // rw-rw-rw
    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
        errExit("open");

    for (ap = 2; ap < argc; ap++)
    {
        switch(argv[ap][0])
        {
            case 'r':
            case 'R':
                // use [1] to get '10000' from 'r10000'
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);

                buf = malloc(len);
                if (buf == NULL)
                    errExit("malloc");
                
                numRead = read(fd, buf, len);
                if (numRead == -1)
                    errExit("read");

                if (numRead == 0)
                {
                    printf("%s: end-of-file\n", argv[ap]);
                }
                else
                {
                    printf("%s: ", argv[ap]);
                    for (j = 0; j< numRead; j++)
                    {
                        if (argv[ap][0] == 'r')
                            // If a char is printable ascii?, print it or print '?'
                            printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');
                        else
                            // print in hexadecimal
                            printf("%02x", (unsigned char) buf[j]);
                    }
                    printf("\n");
                }
                
                free(buf);
                break;
            
            case 'w':
                // When argv[ap] is like "wabc", write "abc" to file
                numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (numWritten == -1)
                    errExit("write");
                printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
                break;
            
            case 's':
                offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                    errExit("lseek");
                printf("%s: seek succeeded\n", argv[ap]);
                break;

            default:
                cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }
    exit(EXIT_SUCCESS);
}
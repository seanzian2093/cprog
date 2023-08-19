// Implementation of readLine()

#include <unistd.h>
#include <errno.h>
#include "read_line.h"

ssize_t readLine(int fd, void *buffer, size_t n)
{
    ssize_t numRead;
    size_t totRead;
    char *buf;
    char ch;

    if (n <=0 || buffer == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    buf = buffer;

    totRead = 0;
    for (;;)
    {
        // Read from fd into ch
        numRead = read(fd, &ch, 1);

        if (numRead == -1)
        {
            // If interuptted then restart read()
            if (errno = EINTR)
                continue;
            else
                return -1;
        }
        // EOF
        else if (numRead == 0) 
        {
            // If nothing in totRead, i.e., no bytes read, return 0.
            if (totRead == 0)
                return 0;
            else
                // Break the loop and go to line 59,i.e., adding null byte to end
                break;
        }
        else
        {
            // When numRead >0, i.e., read some bytes
            if (totRead < n - 1)
            {
                // increment totRead
                totRead++;
                // Move pointer forward and save ch there, i.e., *buf always points to the end of already-read bytes
                *buf++ = ch;
            }

            // Reach end of a line
            if (ch == '\n')
                break;
        }
    }

    *buf = '\0';
    return totRead;
}
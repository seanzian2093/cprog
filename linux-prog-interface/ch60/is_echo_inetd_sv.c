// A concurrent server that implements the TCP echo service and to be invoked via inetd

#include <syslog.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 4096


int main(int argc, char * argv[])
{
    char buf[BUF_SIZE];
    ssize_t numRead;

    // Read from client socket
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        // Do something and write response back to client socket 
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
        {
            syslog(LOG_ERR, "write() failed: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    // If reaches here, numRead = 0 i.e, EOF or -1, i.e., error
    if (numRead == -1)
    {
        syslog(LOG_ERR, "Error from read(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
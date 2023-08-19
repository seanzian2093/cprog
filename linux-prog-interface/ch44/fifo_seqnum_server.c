// An iterative server using FIFOs

#include <signal.h>
#include "fifo_seqnum.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;

    // Set file creation mask of current process
    umask(0);
    // Create server fifo
    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        errExit("mkfifo %s", SERVER_FIFO);

    // Open server fifo
    serverFd = open(SERVER_FIFO, O_RDONLY);
    if (serverFd == -1)
        errExit("open %s", SERVER_FIFO);

    // Open an extra write descriptor on server fifo so we never see EOF
    dummyFd = open(SERVER_FIFO, O_WRONLY);
    if (dummyFd == -1)
        errExit("open %s", SERVER_FIFO);

    // Ignore SIGPIPE signal, so that if server attempts to write to a client fifo that does not have a reader
    // rather than being sent a SIGPIPE signal(kills a process by default), it receives an EPIPE error from the write()
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        errExit("signal");
    
    for (;;)
    {
        if (read(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
        {
            fprintf(stderr, "Error reading request; discarding\n");
            continue;
        }

        // Build client fifo filename with pid from req, previously created by client
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long) req.pid);
        clientFd = open(clientFifo, O_WRONLY);
        if (clientFd == -1)
        {
            errMsg("open %s", clientFifo);
            continue;
        }

        resp.seqNum = seqNum;
        // Write response to client fifo
        if (write(clientFd, &resp, sizeof(struct response)) != sizeof(struct response))
            fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
        if (close(clientFd) == -1)
            errMsg("close");
        
        seqNum += req.seqLen;
    }
}
// A simple UNIX domain stream socket server

#include "us_xfr.h"
#include "error_functions.c"

#define BACKLOG 5

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // Create a stream socket as server socket
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        errExit("socket");

    // Remove existing server socket file if not exist, ignore
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
        errExit("remove-%s", SV_SOCK_PATH);

    // Initilize addr to null byte
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    // Copy server socket file path to addr.sun_path
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Bind server socket to a local address
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        errExit("bind");
    
    // Make server socket opeon for connections, i.e., listening
    if (listen(sfd, BACKLOG) == -1)
        errExit("listen");
    
    for (;;)
    {
        // Wait for connection. When a connection comes, accept it and return a new socket, cfd, i.e., client socket 
        // Server socket remains open for further connections
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
            errExit("accept");

        // Read from client socket and write to stdout
        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
        {
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                fatal("partial/failed write");
        }

        if (numRead == -1)
            errExit("read");
        
        if (close(cfd) == -1)
            errMsg("read");
    }
}
// A simple UNIX domain stream socket client

#include "us_xfr.h"
#include "error_functions.c"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // Create a stream socket as client socket
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        errExit("socket");

    // Initilize server addr to null byte
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    // Copy server socket file path to addr.sun_path
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Connect client socket, sfd to Server socket at an address, i.e., addr
    if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        errExit("connect");
    
    // Read from stdin and copy and write to client socket
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        if (write(sfd, buf, numRead) != numRead)
            fatal("partial/failed write");
    }

    if (numRead == -1)
        errExit("read");

    exit(EXIT_SUCCESS);       
}

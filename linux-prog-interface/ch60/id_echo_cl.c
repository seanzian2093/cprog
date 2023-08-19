// A client for the UDP echo service
#include "id_echo.h"
#include "error_functions.c"
#include "../ch59/inet_sockets.c"

int main(int argc, char *argv[])
{
    int sfd, j;
    ssize_t numRead;
    size_t len; 
    char buf[BUF_SIZE];

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s: host msg...\n", argv[0]);

    sfd = inetConnect(argv[1], SERVICE, SOCK_DGRAM);
    if (sfd == -1)
        fatal("Could not connect to server socket");
    
    for (j = 2; j < argc; j++)
    {
        len = strlen(argv[j]);
        if (write(sfd, argv[j], len) != len)
            fatal("partial/failed write");

        numRead = read(sfd, buf, BUF_SIZE);
        if (numRead == -1)
            errExit("read");

        printf("[%ld bytes] %.*s\n", (long)numRead, (int)numRead, buf);
    }
    exit(EXIT_SUCCESS);
}
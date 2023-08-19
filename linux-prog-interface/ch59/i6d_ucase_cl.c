// A IPv6 case-conversion client using datagram sockets 

#include "i6d_ucase.h"
#include "error_functions.c"


int main(int argc, char *argv[])
{
    struct sockaddr_in6 svaddr, claddr;
    int sfd, j;
    size_t msgLen;
    ssize_t numBytes;
    socklen_t len;
    char resp[BUF_SIZE];

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s host-address msg...\n", argv[0]);
    
    // Create a datagram socket as client socket
    sfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sfd == -1)
        errExit("socket");

    // Initialize a struct for server address
    memset(&svaddr, 0, sizeof(struct sockaddr_in6));
    svaddr.sin6_family = AF_INET6;
    svaddr.sin6_port = htons(PORT_NUM);
    // Read from argv[1], convert and store at svaddr.sin6_addr, i.e., server address
    if (inet_pton(AF_INET6, argv[1], &svaddr.sin6_addr) == -1)
        fatal("inet_pton failed for address '%s'", argv[1]);

    // Send message to server; echo responses on stdout
    for (j = 2; j < argc; j++)
    {
        msgLen = strlen(argv[j]);
        // Send argv[j] through client socket to server socket
        if (sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in6)) != msgLen)
            fatal("sendto");

        // Read through client socket from server socket (server's response) and save to resp
        numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
        if (numBytes == -1)
            errExit("recvfrom");
        printf("Response %d: %.*s\n", j - 1, (int) numBytes, resp);
    }
    exit(EXIT_SUCCESS);
}
// A IPv6 case-conversion server using datagram sockets 

#include "i6d_ucase.h"
#include "error_functions.c"


int main(int argc, char *argv[])
{
    struct sockaddr_in6 svaddr, claddr;
    int sfd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];
    char claddrStr[INET6_ADDRSTRLEN];

    // Create a datagram socket as server socket
    sfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sfd == -1)
        errExit("socket");

    memset(&svaddr, 0, sizeof(struct sockaddr_in6));
    svaddr.sin6_family = AF_INET6;
    svaddr.sin6_addr = in6addr_any;
    svaddr.sin6_port = htons(PORT_NUM);

    // Bind server socket to a socket fd
    if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in6)) == -1)
        errExit("bind");
    
    for (;;)
    {
        len = sizeof(struct sockaddr_in6);
        // Read from socket and save to buf, get sender's address and save to claddr
        numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
        if (numBytes == -1)
            errExit("recvfrom");
        
        if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr, INET_ADDRSTRLEN) == NULL)
            printf("Could not convert client address to string\n");
        else
            printf("Server received %ld bytes from (%s, %u)\n", (long) numBytes, claddrStr, ntohs(claddr.sin6_port));

        for (j = 0; j < numBytes; j++)
            buf[j] = toupper((unsigned char) buf[j]);
        
        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes)
            fatal("sendto");
    }
}
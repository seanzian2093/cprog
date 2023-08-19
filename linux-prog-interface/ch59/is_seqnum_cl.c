// A client that uses stream sockets

#include <netdb.h>
#include "is_seqnum.h"
#include "error_functions.c"
#include "read_line.c"

int main(int argc, char *argv[])
{
    char *reqLenStr;
    char seqNumStr[INT_LEN];
    int cfd;
    ssize_t numRead;
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s server-host [sequence-len]\n", argv[0]);

    // Call getaddinfo() to obtain a list of addresses that we can try connecting to
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    // Allow for IPv4 and IPv6
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_NUMERICSERV;

    // Use host specified by argv[1]; NULL for loopback address
    if (getaddrinfo(argv[1], PORT_NUM, &hints, &result) != 0)
        errExit("getaddrinfo");
    
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (cfd == -1)
            // On error, try next address
            continue;
        
        if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1)
            // A sucessful binding
            break;
        
        // If come this far, connect() failed, close this socket and try next
        close(cfd);
    }

    if (rp == NULL)
        fatal("Could not bind socket to any address");

    freeaddrinfo(result);

    // Send request by writing to the connected socket
    reqLenStr = (argc > 2) ? argv[2] : "1";
    if (write(cfd, reqLenStr, strlen(reqLenStr)) != strlen(reqLenStr))
        fatal("Partial/failed write (reqLenStr)");
    if (write(cfd, "\n", 1) != 1)
        fatal("Partial/failed write (newline)");
    
    // Receive response from server by reading from socket
    numRead = readLine(cfd, seqNumStr, INT_LEN);
    if (numRead == -1)
        errExit("readLine");
    if (numRead == 0)
        fatal("Unexpected EOF from server");

    printf("Sequence number: %s", seqNumStr);
    exit(EXIT_SUCCESS);
}
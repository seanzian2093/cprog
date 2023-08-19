// An iterative server that uses a stream socket to communicate with clients

#include <netdb.h>
#include "is_seqnum.h"
#include "error_functions.c"
#include "get_num.c"
#include "read_line.c"

#define BACKLOG 50

int main(int argc, char *argv[])
{
    uint32_t seqNum;
    char reqLenStr[INT_LEN];
    char seqNumStr[INT_LEN];
    struct sockaddr_storage claddr;
    int lfd, cfd, optval, reqLen;
    socklen_t addrlen;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
#define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
    char addrStr[ADDRSTRLEN];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    if (argc >1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [init-seq-num]\n", argv[0]);

    seqNum = (argc > 1) ? getInt(argv[1], 0, "init-seq-num") : 0;

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        errExit("signal");

    // hints is used as a criteria for selecting socket address
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    // Allow for IPv4 and IPv6
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

    // Selected socket addresses are stored to result, an array of pointers
    // with hints.ai_flags = ai_passive and host=NULL, getaddrinfo() return a loopback IP address
    if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0)
        errExit("getaddrinfo");
    
    // Walk through returned list untill we find an address structure that can be used to successfully create and bind a socket
    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (lfd == -1)
            // On error, try next address
            continue;
        
        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
            errExit("setsockopt");
        
        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            // A sucessful binding
            break;
        
        // bind() failed, try next address
        close(lfd);
    }

    if (rp == NULL)
        fatal("Could not bind socket to any address");

    // Mark the socket as a listening socket
    if (listen(lfd, BACKLOG) == -1)
        errExit("listen");
    
    freeaddrinfo(result);

    // Handle clients iteratively
    for (;;)
    {
        addrlen = sizeof(struct sockaddr_storage);
        // Wait a connection on to lfd, when it comes, save connecting peer's address to claddr, i.e., client address
        cfd = accept(lfd, (struct sockaddr *) &claddr, &addrlen);
        if (cfd == -1)
        {
            errMsg("accept");
            continue;
        }

        // Translate the client socket address to a location and service name
        if (getnameinfo((struct sockaddr *) &claddr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
            snprintf(addrStr, ADDRSTRLEN, "(%s, %s)", host, service);
        else
            snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
        printf("Connection from %s\n", addrStr);

        // Read client's message which is a new-line terminated string specifying how many seq numbers the client wants
        if (readLine(cfd, reqLenStr, INT_LEN) <= 0)
        // Failed read, skip the request
        {
            close(cfd);
            continue;
        }

        reqLen = atoi(reqLenStr);
        // Illegal request, skip it
        if (reqLen <= 0)
        {
            close(cfd);
            continue;
        }

        // Format print current seqNum into seqNumStr, with a terminating new-line character.
        snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
        // Send it back to client via the socket, specified by cfd
        // Client could assume it has been allocated all the seq numbers in the the range of seqNum to (seqNum + reqLen - 1)
        if (write(cfd, &seqNumStr, strlen(seqNumStr)) != strlen(seqNumStr))
            fprintf(stderr, "Error on write");
        
        // Update current seq number
        seqNum += reqLen;

        if (close(cfd) == -1)
            errMsg("close");
    }
}
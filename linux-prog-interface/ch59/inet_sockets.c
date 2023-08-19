// An Internet domain sockets library

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "inet_sockets.h"
#include "tlpi_hdr.h"

int inetConnect(const char *host, const char *service, int type)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = type;
    // Allow for IPv4 and IPv6
    hints.ai_family = AF_UNSPEC;

    s = getaddrinfo(host, service, &hints, &result);
    if (s != 0)
    {
        errno = ENOSYS;
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            // On error, try next address
            continue;
        
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            // A sucessful binding
            break;
        
        // If come this far, connect() failed, close this socket and try next
        close(sfd);
    }

    freeaddrinfo(result);

    return (rp == NULL) ? -1 : sfd;
}

static int inetPassiveSocket(const char *service, int type, socklen_t *addrlen, Boolean doListen, int backlog)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, optval, s;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = type;
    // Allow for IPv4 and IPv6
    hints.ai_family = AF_UNSPEC;
    // Use wildcard IP address
    hints.ai_flags = AI_PASSIVE;


    s = getaddrinfo(NULL, service, &hints, &result);
    if (s != 0)
        return -1;

    // Walk through returned list untill we find an address structure that can be used to successfully create and bind a socket
    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            // On error, try next address
            continue;
        
        if (doListen)
        {
            if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
            {
                close(sfd);
                freeaddrinfo(result);
                return -1;
            }
        }
        
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            // A sucessful binding
            break;
        
        // bind() failed, try next address
        close(sfd);
    }

    if (rp != NULL && doListen)
    {
        if (listen(sfd, backlog) == -1)
        {
            freeaddrinfo(result);
            return -1;
        }
    }
    if (rp != NULL && addrlen != NULL)
        *addrlen = rp->ai_addrlen;

    freeaddrinfo(result);

    return (rp == NULL) ? -1 : sfd;
}

int inetListen(const char *service, int backlog, socklen_t *addrlen)
{
    return inetPassiveSocket(service, SOCK_STREAM, addrlen, TRUE, backlog);
}

int inetBind(const char *service, int type, socklen_t *addrlen)
{
    return inetPassiveSocket(service, type, addrlen, FALSE, 0);
}

char *inetAddressStr(const struct sockaddr *addr, socklen_t addrlen, char *addrStr, int addrStrlen)
{
    char host[NI_MAXHOST], service[NI_MAXSERV];
    if (getnameinfo(addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV) == 0)
        snprintf(addrStr, addrStrlen, "(%s, %s)", host, service);
    else
        snprintf(addrStr, addrStrlen, "(?UNKNOWN?)");
    
    addrStr[addrStrlen - 1] = '\0';
    return addrStr;
}
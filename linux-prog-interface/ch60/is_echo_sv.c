// A concurrent server that implements the TCP echo service

#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include "../ch37/become_daemon.c"
#include "error_functions.c"
#include "../ch59/inet_sockets.c"
#include "tlpi_hdr.h"

#define SERVICE "echo"
#define BUF_SIZE 500

static void grimReaper(int sig)
{
    int savedErrno;

    savedErrno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

static void handleRequest(int cfd)
{
    char buf[BUF_SIZE];
    ssize_t numRead;

    // Read from client socket
    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
    {
        // Do something and write response back to client socket 
        if (write(cfd, buf, numRead) != numRead)
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
}

int main(int argc, char * argv[])
{
    int lfd, cfd;
    struct sigaction sa;

    if (becomeDaemon(0) == -1)
        errExit("becomeDaemon");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        syslog(LOG_ERR, "Error from sigaction(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    lfd = inetListen(SERVICE, 10, NULL);
    if (lfd == -1)
    {
        syslog(LOG_ERR, "Could not create server socket(%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        // Wait for connection on server socket
        cfd = accept(lfd, NULL, NULL);
        if (cfd == -1)
        {
            syslog(LOG_ERR, "Failure in accept(%s)", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // On successful accept, handle each client request in a child process
        switch(fork())
        {
            // If error on fork() give up on this client and try next
            case -1:
                syslog(LOG_ERR, "Can not create child(%s)", strerror(errno));
                close(cfd);
                break;

            // A child process
            case 0:
                // Server socket is inherited but useless to child process
                close(lfd);
                handleRequest(cfd);
                _exit(EXIT_SUCCESS);
            
            // Parent
            default:
                // Client request is handled by child, no need to keep client socket in parent
                close(cfd);
                // Move on to next client
                break;
        }
    }
}
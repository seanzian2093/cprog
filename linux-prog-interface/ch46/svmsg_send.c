// Using msgsnd() to send a message
#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

#define MAX_MTEXT 1024

struct mbuf {
    long mtype;
    char mtext[MAX_MTEXT];
};

static void usageError(const char *progName, const char *msg)
{
    if (msg != NULL)
        fprintf(stderr, "%s", msg);
    fprintf(stderr, "Usage: %s [-n] msqid msg-type [msg-text]\n", progName);
    fprintf(stderr, "       -n          Use IPC_NOWAIT flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int msqid, flags, msgLen;
    struct mbuf msg;
    int opt;

    flags = 0;
    while((opt = getopt(argc, argv, "n")) != -1)
    {
        if (opt == 'n')
            flags |= IPC_NOWAIT;
        else
            usageError(argv[0], NULL);
    }

    // optind is a external variable defined in unistd.h, it indicates the position of a argument provided to command line, starts at 1
    if (argc < optind + 2 || argc > optind + 3)
        usageError(argv[0], "Wrong number of arguments\n");

    msqid = getInt(argv[optind], 0, "msqid");
    msg.mtype = getInt(argv[optind + 1], 0, "msg-type");

    if (argc > optind + 2)
    {
        msgLen = strlen(argv[optind + 2]) + 1;
        if (msgLen > MAX_MTEXT)
            cmdLineErr("msg-text too long (max: %d characters\n", MAX_MTEXT);
        
        memcpy(msg.mtext, argv[optind + 2], msgLen);
    }
    else
    {
        msgLen = 0;
    }

    // Send message
    if (msgsnd(msqid, &msg, msgLen, flags) == -1)
        errExit("msgsnd");
    
    exit(EXIT_SUCCESS);
}
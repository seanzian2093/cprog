// Header file for fifo_seqnum_server.c and fifo_seqnum_client.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

// Well-known name for server's FIFO
#define SERVER_FIFO "/tmp/seqnum_sv"
// Template for building client FIFO name
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
// Space required for client fifo name
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct request {
    pid_t pid;
    int seqLen;
};

struct response {
    int seqNum;
};
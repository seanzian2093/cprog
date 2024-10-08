// Header file for svmsg_file_server.c and svmsg_file_client.c

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define SERVER_KEY 0x1aaaaaa1

struct requestMsg {
    long mtype;
    int clientId;
    char pathname[PATH_MAX];
};

#define REQ_MSG_SIZE (offsetof(struct requestMsg, pathname) - offsetof(struct requestMsg, clientId) + PATH_MAX)
#define RESP_MSG_SIZE 8192

struct responseMsg {
    long mtype;
    char data[RESP_MSG_SIZE];
};

#define RESP_MT_FAILURE 1
#define RESP_MT_DATA 2
#define RESP_MT_END     3
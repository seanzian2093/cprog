// Delete message queues
// Use ipcs command to check IPCs, including messeag queues

#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.c"

int main(int argc, char *argv[])
{
    int j;
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [msqid...]\n", argv[0]);

    for (j = 1; j< argc; j++)
        if (msgctl(getInt(argv[j], 0, "msqid"), IPC_RMID, NULL) == -1)
            errExit("msgctl %s", argv[j]);
    
    exit(EXIT_SUCCESS);
}

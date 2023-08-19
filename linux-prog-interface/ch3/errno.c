// Use perror() and strerr() function 
#include <stdio.h>
// for strerr()
#include <string.h>
// for EXIT_FAILURE
#include <stdlib.h>
// for open() creat(),
#include <fcntl.h>
// for close()
#include <unistd.h>
#include <assert.h>

void perror(const char *msg);
char * strerror(int);

int main(int argc, char *argv[])
{
    assert(argc >= 3);

    int fd = open(argv[1], atoi(argv[2]), argv[3]);


    if (fd == -1)
    {
        printf("err msg: %s\n", strerror(fd));
        perror("open");
        exit(EXIT_FAILURE);
    }

    return 0;
}
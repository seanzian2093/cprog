// Demo usage of read()

#include "tlpi_hdr.h"
#include "error_functions.c"
#include "get_num.h"
#include <unistd.h>

int main(void)
{
    #define MAX_READ 20
    char buffer[MAX_READ];
    // By default, read() reads characters from terminal up to newline \n, i.e.g enter key
    // read() does not put terminating null character at the end of the string that printf() is being asked to print
    // Additional character might be included so output is strang
    if (read(STDIN_FILENO, buffer, MAX_READ) == -1)
        errExit("read");
    printf("The input data was: %s\n", buffer);
}
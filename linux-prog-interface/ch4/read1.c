// Demo usage of read()

#include "tlpi_hdr.h"
#include "error_functions.c"
#include <unistd.h>

int main(void)
{
    #define MAX_READ 20
    char buffer[MAX_READ + 1];
    ssize_t numRead;
    // By default, read() reads characters from terminal up to newline \n, i.e.g enter key
    // read() does not put terminating null character at the end of the string that printf() is being asked to print
    // Additional character might be included so output is strang
    numRead = read(STDIN_FILENO, buffer, MAX_READ);
    if (numRead == -1)
        errExit("read");
    
    buffer[numRead] = '\0';
    printf("The input data was: %s\n", buffer);
}
// File positioning functions 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long flength(char *fname);

int main(int argc, char *argv[])
{
    assert(argc > 1);

    long int fl = flength(argv[1]);
    printf("%s is %ld long\n", argv[1], fl);
}

long flength(char *fname)
{
    long int length = -1L;
    FILE *fptr;

    fptr = fopen(fname, "rb");
    if (fptr != NULL)
    {
        // Move to position 0 relative to SEEK_END i.e., end of file, SEEK_SET for beginning, SEEK_CUR for current pos
        // So essentially move to end of file
        fseek(fptr, 0L, SEEK_END);
        // ftell() return current position in the file stream, i.e., fptr
        length = ftell(fptr);
        fclose(fptr);
    }
    return length;
}
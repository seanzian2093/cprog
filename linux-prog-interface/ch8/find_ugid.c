// Try ugid_functions.c

#include "ugid_functions.h"
#include "ugid_functions.c"

int main(int argc, char *argv[])
{
    char *endptr;
    uid_t u;
    // u = strtol(argv[1], &endptr, 10);
    // atol and atoi ignores unconverted suffix, and use base 10
    u = atol(argv[1]);
    printf("%ld -> %s\n", (long)u, userNameFromId(u));
}
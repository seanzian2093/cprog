// Determine the version of glibc
#include <stdio.h>
#include <gnu-versions.h>

const char * gnu_get_libc_version(void);
int main(void)
{
    printf("glibc version: %s\n", gnu_get_libc_version());
}
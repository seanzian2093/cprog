// Demonstrate the effect of timezones and locales
// Prerequisite - apt-get install locales locales-all
// ./show_time

// TZ environment variable automatically influences ctime(), localtime(), mktime(), and strftime()
// TZ=":Pacific/Auckland" ./show_time

// LANG=de_DE ./show_time

#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define BUF_SIZ 200

int main(int argc, char *argv[])
{
    time_t t;
    struct tm *loc;
    char buf[BUF_SIZ];

    // Providing empty string as 2nd arg makes setlocale to those specified by environment variable
    if (setlocale(LC_ALL, "") == NULL)
        errExit("setlocale");
    
    t = time(NULL);

    printf("ctime() of time() value is: %s", ctime(&t));

    loc = localtime(&t);
    if (loc == NULL)
        errExit("localtime");

    printf("asctime() of local time is: %s", asctime(loc));

    if (strftime(buf, BUF_SIZ, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
        fatal("strftime returned 0");
    printf("strftime() of local time is: %s\n", buf);

    exit(EXIT_SUCCESS);
}
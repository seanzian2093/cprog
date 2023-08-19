// Demonstrate calendar time

#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

int main(int argc, char *argv[])
{
    time_t t;
    struct tm *gmp, *locp;
    struct tm gm, loc;
    struct timeval tv;

    t = time(NULL);
    printf("Seconds since the Epoch (1st Jan 1970): %ld", (long) t);
    printf("about %6.3f years\n", t / SECONDS_IN_TROPICAL_YEAR);

    // gettimeofday store time info to the value of a pointer that points to a timeval struct
    if (gettimeofday(&tv, NULL) == -1)
        errExit("gettimeofday");
    printf(" gettimeofday() returned %ld secs, %ld microsecs\n", (long)tv.tv_sec, (long)tv.tv_usec);

    // gmtime() converts a time_t value to broken-down time corresponding to UTC or Greenwich Mean Time
    gmp = gmtime(&t);
    if (gmp == NULL)
        errExit("gmptime");
    
    // Save a local copy since *gmp may be modified by asctime() or gmtime()
    gm = *gmp;
    
    printf("Broken down by gmtime(): \n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d\n", gm.tm_year, gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);

    // localtime takes into account timezone
    locp = localtime(&t);
    if (locp == NULL)
        errExit("localtime");
    
    loc = *locp;
    printf("Broken down by localtime(): \n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ", loc.tm_year, loc.tm_mon, loc.tm_mday, loc.tm_hour, loc.tm_min, loc.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n\n", loc.tm_wday, loc.tm_yday, loc.tm_isdst);

    // asctime() converts broken down time to string
    printf("asctime() formats the gmtime() value as: %s", asctime(&gm));
    // ctime() converts time_t to string
    printf("ctime() formats the gmtime() value as: %s", ctime(&t));

    // mktime() converts broken down time to time_t
    printf("mktime() of gmtime() value:    %ld sec\n", (long) mktime(&gm));
    printf("mktime() of localtime() value: %ld sec\n", (long) mktime(&loc));

}
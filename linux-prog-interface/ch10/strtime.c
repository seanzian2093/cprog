// Retrieving and convertng calendar time
// ./strtime "9:39:46pm 1 Feb 2011" "%I:%M:%S%p %d %b %Y"
// ./strtime "9:39:46pm 1 Feb 2011" "%I:%M:%S%p %d %b %Y" "%F %T"
#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"
#include "error_functions.c"

#define SBUF_SIZE 1000

int main(int argc, char *argv[])
{
    struct tm tm;
    char sbuf[SBUF_SIZE];
    char *ofmt;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s input-date-time in-formta [out-format]\n", argv[0]);

    // Use locale settings in conversions
    if (setlocale(LC_ALL, "") == NULL)
        errExit("setlocale");

    memset(&tm, 0, sizeof(struct tm));
    // strptime() parses 1st arg according to 2nd arg and save parsed binary time info at 3rg arg, a pointer
    if (strptime(argv[1], argv[2], &tm) == NULL)
        fatal("strptime");

    // Not set by strptime(), tell mktime() to determine if DST is in effect
    tm.tm_isdst == -1;

    printf("calendar time (seconds, since Epoch): %ld\n", (long)mktime(&tm));

    ofmt = (argc > 3) ? argv[3] : "%H:%M:%S %A, %d %B %X %T %Z";
    // strftime() read from 4th arg, a pointer and format according to 3rd arg
    // and write to 1st arg with no more than 2nd arg
    if (strftime(sbuf, SBUF_SIZE, ofmt, &tm) == 0)
        fatal("strftime returned 0");
    printf("strftime() yields: %s \n", sbuf);

    exit(EXIT_SUCCESS);
}
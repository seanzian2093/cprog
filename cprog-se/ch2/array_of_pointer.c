// Pointers are themselves varialbe so they can be stored in arrays just as other variables can
// int *parray[N] is an array of pointers that point to int
// int (*r)[N] is a pointer that points to an array of int, with size N
// char *argv[] is an array of pointers that point at char or 1st char of a string

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    assert(argc >= 2);
    char *months[] = {
        "illegal",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    };

    int i, j;
    i = atoi(argv[1]);
    if (i < 1 || i > 12)
        i = 0;

    printf("Month number %d is %s.\n", i, months[i]);
    printf("The letters of the month are: ");
    for (j = 0; months[i][j] != '\0'; ++j)
        printf("%c", months[i][j]);
    printf("\n");

}
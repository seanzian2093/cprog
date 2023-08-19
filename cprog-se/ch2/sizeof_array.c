// Demo that sizeof() only return the size of array if it refers to the original array name
/* An array name is automatically converted to a pointer in an expression so that any other reference to the array
   will not be an array name but a pointer*/

#include <stdio.h>

int count_days(int days[], int len);

int main(void)
{
    // days[12] is not needed but automatically determined by initializers
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // sizeof on original array name returns to 12 * sizeof(int)
    int size = sizeof(days);
    printf("size of days: %d\n", size);

    // Number of element
    int nelems = sizeof(days) / sizeof(days[0]);
    for (int i = 0; i < nelems; i++)
        printf("Month %d has %d days.\n", i+1, days[i]);
    
    // Any reference to array other than original array name converts array to a pointer
    int *pdays = days;
    // Pointer has sizeof 8
    printf("sizeof(days) = %ld\n", sizeof(days));
    // Integer has sizeof 4
    printf("sizeof(days + 1) = %ld\n", sizeof(days + 1));
    printf("int *pdays=days; sizeof(pdays) = %ld\n", sizeof(pdays));

    count_days(days, nelems);

    return 0;
}

int count_days(int days[], int len)
{
    int total = 0;
    //sizeof on array function parameter will return size of int
    printf("sizeof(days) = %ld\n", sizeof(days));
    printf("sizeof(days[0]) = %ld\n", sizeof(days[0]));
    printf("sizeof(days) / sizeof(days[0]) = %ld\n", sizeof(days) / sizeof(days[0]));
    while(len--)
        total += days[len];

    printf("total = %d\n", total);
    return total;
}
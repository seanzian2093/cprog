//Determine the ranges of char, short, int and long, both signed and unsigned
#include <stdio.h>
#include <limits.h>
#include <string.h>

long int power(int base, int n);
void sizeinfo(int size, int issigned, char names[]);
void limitsinfo(int bits, long int min, long int max, char names[]);

int main(void)
{
    int size;
    char names[50];
    // unsigned char
    strcpy(names, "unsigned char");
    size = sizeof(unsigned char) * 8;
    sizeinfo(size, 0, names);
    limitsinfo(CHAR_BIT, 0, UCHAR_MAX, names);

    // signed char
    strcpy(names, "signed char");
    size = sizeof(signed char) * 8;
    sizeinfo(size, 1, names);
    limitsinfo(CHAR_BIT, SCHAR_MIN, SCHAR_MAX, names);

    // unsigned short int
    strcpy(names, "unsigned short int");
    size = sizeof(unsigned short int) * 8;
    sizeinfo(size, 0, names);
    limitsinfo(0, 0, USHRT_MAX, names);

    // signed short int 
    strcpy(names, "signed short int");
    size = sizeof(signed short int) * 8;
    sizeinfo(size, 1, names);
    limitsinfo(0, SHRT_MIN, SHRT_MAX, names);

    // unsigned int
    strcpy(names, "unsigned int");
    size = sizeof(unsigned int) * 8;
    sizeinfo(size, 0, names);
    limitsinfo(0, 0, UINT_MAX, names);

    // signed int 
    strcpy(names, "signed int");
    size = sizeof(signed int) * 8;
    sizeinfo(size, 1, names);
    limitsinfo(0, INT_MIN, INT_MAX, names);

    // unsigned long int
    strcpy(names, "unsigned long int");
    size = sizeof(unsigned long int) * 8;
    sizeinfo(size, 0, names);
    limitsinfo(0, 0, ULONG_MAX, names);

    // signed int 
    strcpy(names, "signed long int");
    size = sizeof(signed long int) * 8;
    sizeinfo(size, 1, names);
    limitsinfo(0, LONG_MIN, LONG_MAX, names);

}

void limitsinfo(int bits, long int min, long int max, char names[])
{
    printf("From limits.h:\n");
    printf("Bits in a %s: %d\n", names, bits);
    printf("Min of a %s: %ld\n", names, min);
    printf("Max of a %s: %ld\n", names, max);
    printf("\n");
}
void sizeinfo(int size, int issigned, char names[])
{
    long int min, max;
    // unsigned
    if (issigned == 0)
    {
        min = 0;
        max = power(2, size) - 1;
    }
    // signed
    else
    {
        min = -1 * power(2, size)/2;
        max = power(2, size)/2 - 1;
    }

    printf("By computation:\n");
    printf("Bits of %s: %d\n", names, size);
    printf("Min of %s: %ld\n", names, min);
    printf("Max of %s: %ld\n", names, max);
    printf("\n");
}

long int power(int base, int n)
{
    long int p = 1; 
    for (p = 1; n > 0; n--)
    {
        p = p * base;
    }
    return p;
}
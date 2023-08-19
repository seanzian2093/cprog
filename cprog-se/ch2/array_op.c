// A collection of valid operations on various array types

#include <stdio.h>

int main(void)
{
    short val = 9;
    printf("val is %d, stored at %p\n", val, &val);
    short *pval = &val;
    printf("pval is %p, points to value %d\n", pval, *pval);
    double array[] = {1.0, 2.0, 3.0};
    printf("array is %p\n", array);
    double *parray = array;
    printf("parray is %p\n", parray);
    // array is read-write
    char str[] = "Hello World!";
    printf("str is %s, initial location is %p\n", str, str);
    str[1] = 'a';
    printf("str is %s, initial location is %p\n", str, str);

    printf("string constant is %s, initial location is %p\n", "Hello World!", "Hello World!");
    return 0;
}
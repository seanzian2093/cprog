// Pointers in C.C++ freeCodeCamp.org@in youtube

#include <stdio.h>

int main(void)
{
    int a = 1025;
    int *p;
    p = &a;

    // add const to pointer
    printf("Adress that p points to is: %ld\n", p);
    printf("size of int: %ld bytes\n", sizeof(int));
    printf("Adress that p+1 points to is: %ld\n", p+1);
    printf("Value at p+1 is undefined, garbaga: %d\n", *(p+1));

    // verify
    printf("a's address: %ld\n", &a);
    // Make sure to cast &a to long int ,other wise it is still pointer arithmetic,i.e. the increament will be 4*4=16
    printf("a's address:%ld + sizeof int: %ld: %ld\n", (&a), sizeof(int), ((long int)&a + sizeof(int)));


    printf("\n");
    // pointer type
    char * p0;
    // Must cast, otherwise compiler will complaint
    p0 = (char *)p;
    printf("size of char is %ld bytes\n", sizeof(char));
    // Since size of char is 1 byte, p0 will take only 8bit or 1 byte, the value is not straightforward
    // 1025 = 00000000 00000000 00000100 00000001
    // p0 will take last bytes,i.e. 00000001, which is 1 in decimal
    printf("Address = %ld, value = %d\n", p0, *p0);
    // similarly po+1 take 00000100 i.e. 4 in decimal
    printf("Address = %ld, value = %d\n", p0+1, *(p0+1));

    printf("\n");
    // void pointer - generic type
    void *p1;
    p1 = p;
    // Since p1 points to void, * operator is not allowed
    printf("Address = %ld, value = %d\n", p1, *p1);

}

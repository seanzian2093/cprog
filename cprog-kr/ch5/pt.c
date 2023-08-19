// How to declare a pointer and how to use & and *
#include <stdio.h>

int main(void)
{
    int x = 1, y = 2, z[10];
    // Declare ip, a pointer that points to an integer which is not defined yet
    int *ip;

    // Let ip point to x by assign x's address to ip
    ip = &x;
    printf("ip = &x: \n");
    printf("ip or the address is: %p\n", ip);
    printf("value at that address is: %d\n", *ip);
    printf("\n");
    // Use *ip to get the value stored at the address ip is pointing to
    // Assign the value to y 
    y = *ip;
    printf("y = *ip: \n");
    printf("ip or the address is: %p\n", ip);
    printf("value at that address is: %d\n", *ip);
    printf("\n");
    // Similarly asign a new value to be the value stored at the address
    *ip = 0;
    printf("*ip = 0: \n");
    printf("ip or the address is: %p\n", ip);
    printf("value at that address is: %d\n", *ip);
    printf("\n");
    // ip now points to z[0]
    ip = &z[0];
    printf("ip = &z[0]: \n");
    printf("ip or the address is: %p\n", ip);
    printf("value at that address is: %d\n", *ip);
}
// C Programming in Linux - chapter1_3.c
// gcc -o hello3 chapter1_3.c

#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    printf("Content-type:text/plain\n\n");
    printf("Hello, you are still learning C!!\n");
    printf("Number of arguments to the main function: %d\n", argc);
    
    for (i = 0; i < argc; i++)
        printf("argument number %d is %s\n", i, argv[i]);

    return 0;
}
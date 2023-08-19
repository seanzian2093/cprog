// C Programming in Linux - ch1_4.c
// gcc -o ch1_4 ch1_4.c
// sudo mv ch1_4 /usr/lib/cgi-bin

#include <stdio.h>

// Seldomly documented third argument to main()
int main(int argc, char *argv[], char *env[])
{
    int i = 0;
    printf("Content-type:text/plain\n\n");
    printf("Hello, you are still learning C!!\n");
    printf("Number of arguments to the main function: %d\n", argc);
    
    for (i = 0; i < argc; i++)
        printf("argument number %d is %s\n", i, argv[i]);

    i = 0;
    printf("Environment variable:\n");
    while (env[i])
    {
        printf("env[%d] = %s\n", i, env[i]);
        i++;
    }
    return 0;
}
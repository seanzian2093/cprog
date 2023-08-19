// C programming in Linux - ch3_1
// The math library must be linked in when building the executable
// The math library is named libm.so, and the -l option assumes a lib prefix and .a or .so suffix
// gcc ch3_1.c -o ch3_1 -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double doit(int n1, int n2)
{
    return sqrt((double) (n1 + n2));
}

int main(int argc, char *argv[])
{
    int n1 = 0, n2 = 0, i = 0;
    n1 = atoi((char *)strtok(argv[1], ":"));
    n2 = atoi((char *)strtok(NULL, ":"));
    printf("Content-type:text/html\n\n");
    printf("<html>\n");
    
    for (i = 0; i <= 100; i++)
        printf("%f, ", doit(n1 + i, n2 * i));

    printf("</body>\n");
    printf("</html>\n");

    return 0;
}

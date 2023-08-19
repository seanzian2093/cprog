// Show difference of e,f,g format when using printf

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float f = 214.52;
    // %f prints the number as decimal floating point number
    // Use %% to printf a %
    printf("%%f: %f\n", f);
    // %e prints the number in scientific notation
    // Or use %c
    printf("%ce: %e\n", '%', f);
    // %g prints in shortest among %f and %e
    // Or use %s
    printf("%sg: %g\n", "%", f);

    if (argc > 1)
    {
        float dl = atof(argv[1]);
        printf("f: %f\n", dl);
        printf("e: %e\n", dl);
        printf("g: %g\n", dl);
    }
}

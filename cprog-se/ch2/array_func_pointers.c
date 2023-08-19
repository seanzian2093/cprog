// Show defining and use an array of function pointers
// int (*pf[10])(char *) - this is an array of pointers to functions; each func has same interface;

#include <stdio.h>
#include <assert.h>

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mult(double a, double b) { return a * b; }
double divi(double a, double b) { assert(b != 0.0); return a / b; }

int main(void)
{
    int i;
    double val1, val2;
    // Define an array of pointers that point to function; those function all takes 2 double input
    double (*pf[])(double, double) = { add, sub, mult, divi };
    printf("Enter two floating-point values, and an integer between 0 and 3: ");
    scanf("%lf%lf%d", &val1, &val2, &i);
    if (i < 0 || i > 3)
        i = 0;
    
    printf("Performing operation %d on %3.2f and %3.2f equals to %3.2f\n", i, val1, val2, pf[i](val1, val2));

    return 0;
}
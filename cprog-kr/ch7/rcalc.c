// Rudimentary calculator

#include <stdio.h>

int main(void)
{
    double sum, v;

    sum = 0;
    // scanf return number of input read
    // l for long; h for short
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum +=v);
    return 0;
}
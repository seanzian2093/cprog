// Second version - using floaing-point arithmetic instead of integer 
// Exercise 1-3
#include <stdio.h>

int main(void)
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("Fahr to Celsius:\n");
    while(fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
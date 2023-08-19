// Second version - using floaing-point arithmetic instead of integer 
// Exercise 1-5
#include <stdio.h>

int main(void)
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;

    celsius = upper;
    printf("Celsiusto Fahr:\n");
    while(celsius >= lower) {
        fahr = (9.0/5.0) * (celsius + 32.0);
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius = celsius - step;
    }
}
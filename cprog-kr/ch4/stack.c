// Define stack pop and push function
#include <stdio.h>
#include "calc.h"
// Maximum depth of the val stack
#define MAXVAL 100

// Next free stack position
static int sp = 0;
// Value stack
static double val[MAXVAL];

// Push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        // Store f at sp position and increase sp by 1
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// Pop and return top value from stack
double pop(void)
{
    if (sp > 0)
        // Reduce sp by 1 and use it
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
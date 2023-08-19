// Use function pointers to pass function as arguments to another function
// int (*pf)(char) - this is a pointer to function pf; pf takes char as input, return int
// int (*pf[])(char) - this is an array of pointers to functions; each func has same interface;
// int *f(char) - this is a function, take char, return pointer to int

// In a function declaration it is possible to declare a function pointer without using an identifier, similar to arg
// void myfunc(char *, int, unsigned (*) (int)); 3rd arg is a pointer to func which takes int, return unsigned int
// void myfunc(char *msg, int nloops, unsigned (*convert)(int n));

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mult(double a, double b) { return a * b; }
double divi(double a, double b) { assert(b != 0.0); return a / b; }

// 1st arg is a pointer to a func: f(double, double)
void exec_op(double (*f)(double, double), double x, double y)
{
    // Though f is a pointer to func but to its name is converted to pointers automatically, like array
    // no need to use address-of operator &
    double result = f(x, y);
    printf("Result of operation on %3.2f and %3.2f is %7.4f\n", x, y, result);
}

int main(int argc, char *argv[])
{
    assert(argc >= 3);
    double val1 = atof(argv[1]);
    double val2 = atof(argv[2]);

    exec_op(add, val1, val2);
    exec_op(sub, val1, val2);
    exec_op(mult, val1, val2);
    exec_op(divi, val1, val2);
}
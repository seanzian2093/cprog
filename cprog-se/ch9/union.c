// Basic of union

#include <stdio.h>

int main(void)
{
    // Similar as struct, define a union type named Utype
    union Utype {
        int ival;
        float fval;
        char *sval;
    };

    // Use Utype to declare x
    union Utype x;
    // Assign value to a member
    x.fval = 56.4;
    // Access member
    printf("%f\n", x.fval);
    // Implementation dependent
    printf("%d\n", x.ival);
}
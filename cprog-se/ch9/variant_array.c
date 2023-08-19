// Basic of union - variant array

#include <stdio.h>

int main(void)
{
    // Define a new type based on Union
    typedef union {
        int ival;
        float fval;
    } Utype;

    enum { INT, FLOAT };

    // Define a new type named VariantType based on struct
    typedef struct {
        // Tga for current stored type
        int type;
        // Storage for variant type
        Utype val;
    } VariantType;

    // Declare a heterogeneous array
    VariantType array[50];

    array[0].val.ival = 56;
    array[0].type = INT;

    array[1].val.fval = 56.0;
    array[1].type = FLOAT;
    
    // Print array
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
        if (array[i].type == INT)
            printf("%d\n", array[i].val.ival);
        else if (array[i].type == FLOAT)
            printf("%f\n", array[i].val.fval);
        else
            printf("Unknown type\n");


}

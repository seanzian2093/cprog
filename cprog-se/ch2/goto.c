// Demo goto basic idea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
enum {VAL1 = 'a', VAL2 = 'b', VAL3 = 'Z'};

int main(void)
{
    char a[SIZE], b[SIZE];
    int i, j;

    // Initialize arrays so they are different from each other
    memset(a, VAL1, SIZE);
    memset(b, VAL2, SIZE);

    // Set a random element in each array to VALUE
    a[rand()%SIZE] = VAL3;
    b[rand()%SIZE] = VAL3;

    // Search for location of common elements
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (a[i] == b[j])
                goto found;
    
    // Error: match not found
    printf("Did not find any common elements!!\n");
    return 0;

// found is a named label, must always be followed by a statement even a null, i.e., ;
found:
    printf("a[%d] = %c and b[%d] = %c\n", i, a[i], j, b[j]);
}

// Show defining, declaring and using of mult-dim array

#include <stdio.h>
#define SIZE 3

// int (*r)[N] is a pointer that points to an array of int, with size N
void multiply(int (*r)[SIZE], const int a[][SIZE], const int b[SIZE][SIZE]);

int main(void)
{
    int m1[][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int m2[SIZE][SIZE] = { 0 };

    int i, j;
    multiply(m2, m1, m1);

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            printf("%3d ", m2[i][j]);
        printf("\n");
    }
    return 0;
}

void multiply(int (*r)[SIZE], const int a[][SIZE], const int b[SIZE][SIZE])
{
    int i, j, k;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            for (k = 0; k < SIZE; k++)
                r[i][j] += a[i][k] * b[k][j];
}
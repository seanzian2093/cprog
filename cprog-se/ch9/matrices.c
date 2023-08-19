// A more compex example of dynamic memory
#include <stdio.h>
#include <assert.h>

// create_matrix() returns a pointer that points to a pointer which points to a double
// pointer-to-a-pointer is similar to mult-dim array
// Pointers referring to dynamically allocated memory may be safely returned by a function
// as the memory continues to be valid until explicitly destroyed.
double **create_matrix(int m, int n);
// Destroy a m * n matrix
void destroy_matrix(double **p, int m, int n);

int main(void)
{
    double **m1, **m2;
    m1 = create_matrix(2, 3);
    m2 = create_matrix(3, 4);

    // Initialize the matrix element

    // Performance some matrix operations

    destroy_matrix(m1, 2, 3);
    destroy_matrix(m2, 3, 4);

}

double **create_matrix(int m, int n)
{
    double **p;
    int i;
    assert(m > 0 && n > 0);

    // Allocate a block of memory for entire matirx - m rows
    // Each row is an array of double or a pointer to double, so size should be sizeof(double *)
    p = (double **)malloc(m * sizeof(double *));
    // Always check result of malloc() against NULL
    if (p == NULL)
        return p;
    
    // Allocate memory for each row which is of n double elements
    for (i = 0; i < m; i++)
    {
        p[i] = (double *)malloc(n * sizeof(double));
        if (p[i] == NULL)
            goto failed;
    }
    return p;

failed:
    // If fails, free each p[i] that was successfully allocated memory
    for (--i; i >=0; --i)
        free(p[i]);
    // After that free p; not the other way
    free(p);
    return NULL;
}

void destroy_matrix(double **p, int m, int n)
{
    int i;
    assert(m > 0 && n > 0);

    for (i = 0; i < m; ++i)
        free(p[i]);
    free(p);
}
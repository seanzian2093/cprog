// find x in v[0] <= v[1] <= ... <= v[n-1]
#include<stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
    int x, ret;
    int v[10] = {1,2,3,4,5,6,7,8,9,10};

    printf("Please input an integer: ");
    scanf("%d", &x);
    ret = binsearch(x, v, 10);
    printf("x is found at: %d\n", ret);
}
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid + 1;
        else if (x > v[mid])
            low = mid + 1;
        else
        // found match
            return mid;
    }
    // no match
    return -1; 
}
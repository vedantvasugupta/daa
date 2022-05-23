//code to find sqrt in c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float find_root(float low, float high, float n);
int main()
{
    float n;
    printf("Enter the number: ");
    scanf("%f", &n);
    clock_t t;
    t = clock();
    printf("\n%f", find_root(0, n, n));
    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
}
float find_root(float low, float high, float n)
{
    float mid = (low + high) / 2;
    if ( high-low < 0.00001 && high-low > -0.00001)
    {
        return mid;
    }
    else if (n - mid * mid > 0)
    {
        return find_root(mid, high, n);
    }
    else
    {
        return find_root(low, mid, n);
    }
}

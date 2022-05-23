//tournament way to find max in an array
#include <stdio.h>
#include <stdlib.h>

struct ans
{
    int max;
    int min;
};

struct ans find_max(int array[], int n);

int main()
{
    int n = 0;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the %d number: ", i + 1);
        scanf("%d", &array[i]);
    }
    printf("\nmax and min %d %d", find_max(array, n).max, find_max(array, n).min);
}
struct ans find_max(int array[], int n)
{
    if (n == 1)
    {
        struct ans maxmin;
        maxmin.max = array[0];
        maxmin.min = array[0];
        return maxmin;
    }
    else if (n == 2)
    {
        if (array[0] >= array[1])
        {
            struct ans maxmin;
            maxmin.max = array[0];
            maxmin.min = array[1];

            return maxmin;
        }
        else
        {
            struct ans maxmin;
            maxmin.max = array[1];
            maxmin.min = array[0];
            return maxmin;
        }
    }
    else
    {

        struct ans maxmin;
        int half = n / 2;
        int left_array[half];
        for (int i = 0; i < half; i++)
        {
            left_array[i] = array[i];
        }
        int right_array[n - half];
        for (int i = 0; i < n - half; i++)
        {
            right_array[i] = array[i + half];
        }
        struct ans left = find_max(left_array, half);

        struct ans right = find_max(right_array, n - half);

        if (left.max > right.max)
        {
            maxmin.max = left.max;
        }
        else
        {
            maxmin.max = right.max;
        }
        if (left.min < right.min)
        {
            maxmin.min = left.min;
        }
        else
        {
            maxmin.min = right.min;
        }
        return maxmin;
    }
}
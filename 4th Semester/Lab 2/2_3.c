//pair wise method to find max

#include <stdio.h>
#include <stdlib.h>

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
    int max, min;
    if (n % 2 == 0)
    {
        if (array[0] > array[1])
        {
            max = array[0];
            min = array[1];
        }
        else
        {
            max = array[1];
            min = array[0];
        }
    }
    else
    {
        max = array[0];
        min = array[0];
    }
    for (int i = 1; i < n; i = i + 2)
    {
        if (n % 2 == 0 && i == 1)
        {
            i++;
        }
        if (array[i] > array[i + 1])
        {
            if (array[i] > max)
                max = array[i];
            if (array[i + 1] < min)
                min = array[i + 1];
        }
        else
        {
            if (array[i + 1] > max)
                max = array[i + 1];
            if (array[i] < min)
                min = array[i];
        }
    }

    printf("%d %d", max, min);
}
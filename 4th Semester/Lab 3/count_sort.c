//count sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n = 10;
    int array[] = {35, 25, 15, 5, 14, 18, 16, 13, 17, 19};
    clock_t t;
    t = clock();
    function(&array[0], n);
    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
}
void function(int *array, int n)
{
    int max;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            max = array[i];
        }
        else
        {
            if (max < array[i])
            {
                max = array[i];
            }
        }
    }
    printf("\nThis is the max of the array: %d\n", max);
    int new_array[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        new_array[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        new_array[array[i]] += 1;
    }
    int final_array[n];
    int count = 0;
    for (int i = 0; i < max + 1; i++)
    {
        while (new_array[i] > 0)
        {
            final_array[count] = i;
            count++;
            new_array[i]--;
        }
    }
    printf("\nThis is the final array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", final_array[i]);
    }
}

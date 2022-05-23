//code for radix sort in c

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
    int n = 10;
    int array[] = {35, 25, 15, 5, 14, 18, 16, 13, 17, 19};
    clock_t t;
    t = clock();

    int limit = 0;
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < array[i])
            max = array[i];
    }
    while (max != 0)
    {
        max = max / 10;
        limit++;
    }
    int copy_array[n];
    for (int i = 0; i < n; i++)
    {
        copy_array[i] = array[i];
    }
    int tbs[n];
    int order[n];
    int final[n];

    for (int k = 0; k < limit; k++)
    {
        for (int i = 0; i < n; i++)
        {
            tbs[i] = copy_array[i] % 10;
            copy_array[i] = copy_array[i] / 10;
            order[i] = i;
        }
        function(&tbs[0], &order[0], n);
        int copy2[n];
        for (int j = 0; j < n; j++)
        {
            copy2[j] = copy_array[order[j]];
        }
        for (int j = 0; j < n; j++)
        {
            copy_array[j] = copy2[j];
        }

        for (int j = 0; j < n; j++)
        {
            final[j] = array[order[j]];
        }
        for (int j = 0; j < n; j++)
        {
            array[j] = final[j];
        }
    }
    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
    printf("\nfinal order: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", final[i]);
    }
}

void function(int *array, int *order, int n)
{

    int max;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            max = *(array + i);
        }
        else
        {
            if (max < *(array + i))
            {
                max = *(array + i);
            }
        }
    }
    int new_array[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        new_array[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        new_array[array[i]] += 1;
    }
    int count = 0;

    for (int i = 0; i < max + 1; i++)
    {

        while (new_array[i] > 0)
        {
            for (int j = 0; j < n; j++)
            {
                if (*(array + j) == i)
                {
                    *(array + j) = -1;
                    *(order + count) = j;
                    break;
                }
            }
            count++;
            new_array[i]--;
        }
    }
}

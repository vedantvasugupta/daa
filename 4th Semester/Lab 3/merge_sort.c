//merge sort in c

#include <stdio.h>
#include <time.h>
int main()
{
    int n = 10;
    int array[] = {35, 25, 15, 5, 14, 18, 16, 13, 17, 19};
    clock_t t;
    t = clock();
    merge_sort(array, 0, n - 1);

    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
}

void merge_sort(int *array, int low, int high)
{
    printf("\nLow and high refcieved: %d %d", low, high);
    if (high - low == 0)
    {
        printf("\n1 size array recieved this is what we are returning: %d", array[low]);

        return;
    }
    else if (high - low == 1)
    {
        if (array[high] < array[low])
        {
            int temp = array[high];
            array[high] = array[low];
            array[low] = temp;
        }
        printf("\n2 size array recieved this is what we are returning: %d %d", array[low], array[high]);
        return;
    }
    else
    {
        int mid = (high + low) / 2;
        printf("\nUnsorted array recieved: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d ", array[i]);
        }
        merge_sort(array, low, mid);
        merge_sort(array, mid + 1, high);
        printf("\nInparts sorted array: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d ", array[i]);
        }
        for (int i = low + 1; i <= high; i++)
        {
            if (array[i] < array[i - 1])
            {
                for (int j = i; j > low; j--)
                {
                    if (array[j] < array[j - 1])
                    {
                        int temp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = temp;
                    }
                }
            }
        }
        printf("\nSorted array: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d ", array[i]);
        }
        return;
    }
}


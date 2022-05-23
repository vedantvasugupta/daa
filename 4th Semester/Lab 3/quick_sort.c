//quick sort for array in c
#include <time.h>
#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    quickSort(array, 0, n - 1);
}

void quickSort(int *array, int low, int high)
{
    // time(sleep(1));

    printf("\nThese are thr highs and lows: %d %d ", high, low);

    if (high - low < 1)
    {
        return;
    }
    if (high - low == 1)
    {
        printf("\nRecieved array of size 1: ");
        if (array[low] > array[high])
        {
            int temp = array[low];
            array[low] = array[high];
            array[high] = temp;
        }
        return;
    }
    else
    {
        int i, j;
        printf("\nThe array recieved: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d ", array[i]);
        }
        int pivot = high;
        printf("\nThe pivot is %d", array[pivot]);
        for (i = low, j = high - 1; i <= j;)
        {
            // time(sleep(1));

            while (array[i] <= array[pivot])
            {
                i++;
                if (i == pivot)
                {
                    break;
                }
                if (i > j)
                {
                    break;
                }
            }
            while (array[j] >= array[pivot])
            {
                j--;
                if (j == low)
                {
                    j = low;
                    break;
                }
                if (i > j)
                {
                    break;
                }
            }
            if (i > j ||i==pivot)
            {
                break;
            }
            else if (j < low)
            {
                j = low;
                break;
            }
            else if (j == low)
            {
                // i = low;
                j = low;
                break;
            }
            else
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;

                printf("\nSwapping %d and %d", array[j], array[i]);
            }
        }
        int temp = array[pivot];
        array[pivot] = array[i];
        array[i] = temp;
        printf("\nThe i and j are now %d and %d respectively", i, j);
        printf("\nThe array before recursion is: ");
        for(int k=low; k <= high; k++)
        {
            printf("%d ", array[k]);
        }
        if(low!=j && j>low)
        quickSort(array, low, j);
        if(i+1!=high && high>low)
        quickSort(array, i + 1, high);
        printf("\e[1;1H\e[2J");
        printf("\nThe sorted array: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d ", array[i]);
        }
    }
}

//insertion sort in c

#include <stdio.h>
#include <time.h>
int main()
{
    clock_t t;
    t = clock();
    int n = 10;
    int array[] = {35, 25, 15, 5, 14, 18, 16, 13, 17, 19};

    for (int i = 1; i < n; i++)
    {
        if (array[i] < array[i - 1])
        {
            for (int j = i; j > 0; j--)
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
    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n",(float)t,((float)t) / CLOCKS_PER_SEC);
    printf("This is a sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}
#include <stdio.h>
int main()
{
    int n;
    printf("Enter the number of days in the data set: ");
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    pwc(array, n);
}

void pwc(int array[], int n)
{
    int lt = 1;
    int rt = n - 1;

    while (lt <= rt)
    {
        int mid = (lt + rt) / 2;
        printf(" This is mid: array[%d] = %d \n", mid, array[mid]);
        if (array[mid] > array[mid + 1] && array[mid - 1] < array[mid])
        {
            printf("%d ", array[mid]);
            return 0;
        }
        else if (array[mid] < array[mid + 1])
        {
            lt = mid + 1;
            printf("This is the new lt: %d ", lt);
            printf("case 1");
        }
        else if (array[mid - 1] > array[mid])
        {
            rt = mid;
            printf("case 2");
        }
    }
}

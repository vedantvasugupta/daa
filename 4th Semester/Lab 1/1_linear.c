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
    int peaks_array[n];
    int count = 0;

    for (int i = 1; i < n-1; i++)
    {
        if (array[i] > array[i - 1] & array[i] > array[i + 1])
        {
            peaks_array[count] = array[i];
            count++;
        }
    }
    int max =-1;
    for (int i = 0; i < count; i++)
    {
        if (peaks_array[i]>max)
        {
            max=peaks_array[i];
        }
        
    }
    printf("\n%d\n", max);
}
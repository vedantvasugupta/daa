//linear way to find max

#include <stdio.h>


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

    int max = -9999999;
    for (int i=0; i<n; i++)
    {
        if(array[i]>max)
        {
            max = array[i];
        }
    }
    printf("The max of the array is: %d\n", max);
    int min = 9999999;
    for (int i=0; i<n; i++)
    {
        if(array[i]<min)
        {
            min = array[i];
        }
    }
    printf("The min of the array is: %d", min);
}
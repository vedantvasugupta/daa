#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int number;
    int flag;
};

int main()
{
    int n;
    printf("Enter the number whose primality you want to check: ");
    scanf("%d", &n);
    struct node array[n+1];
    for (int i = 0; i <= n; i++)
    {
        array[i].number = i;
        array[i].flag = 0;
    };
    array[0].flag=1;
    array[1].flag=1;
    for(int i=2;i<n;i++)
    {
        if(array[i].flag==0)
        {
            for(int j=array[i].number*array[i].number;j<=n;j+=array[i].number)
            {
                array[j].flag=1;
            }
        }
    }
    printf("\nThe prime numbers lesser than equal to %d are: ", n);
    for (int i = 0; i <= n; i++)
    {
        if (array[i].flag == 0)
        {
            printf("%d ", array[i].number);
        }
    }
}


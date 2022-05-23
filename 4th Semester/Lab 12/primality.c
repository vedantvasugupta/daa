// code for primality in c

#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    printf("Enter the number you want to test for primality: ");
    scanf("%d", &n);
    if (n == 1)
    {
        printf("1 is not a prime number");
    }
    else
    {
        int i, flag = 0;
        for (i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("%d is a prime number", n);
        }
        else
        {
            printf("%d is not a prime number", n);
        }
    }


}
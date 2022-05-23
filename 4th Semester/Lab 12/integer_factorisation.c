// code for integer factorisation in c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n;
    int *array = (int *)malloc(sizeof(int));
    int count;
    printf("Enter the number you want to factorise: ");
    scanf("%d", &n);
    int n_orignal = n;
    for (int i = 2; i <= n_orignal/2; i++)
    {
        if (is_prime_c(i))
        {
            if (n % i == 0)
            {
                *(array + count) = i;
                count++;
                array = (int *)realloc(array, sizeof(int) * (count + 1));
                n = n / i;
                i--;
                if (n == 1)
                {
                    break;
                }
            }
        }
    }
    printf("The factors of %d are: ", n_orignal);
    for (int i = 0; i < count; i++)
    {
        printf("%d ", *(array + i));
    }
}

int is_prime_c(int n)
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
        return 1;
    }
    else
    {
        return 0;
    }
}
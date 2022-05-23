// this is code for bellman ford in c 

#include <stdio.h>
#define n 5

int main()
{
    int weight_matrix[n][n] = {};
    int weights[] = {6, -2, 3, 2, 4, 5, 3, -1, 3, 3};
    int ticker = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            weight_matrix[i][j] = weights[ticker];
            weight_matrix[j][i] = weights[ticker];
            ticker++;
        }
    }
    // print weight matrix
    printf("weight matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", weight_matrix[i][j]);
        }
        printf("\n");
    }
    int cost_matrix[]={0,99999,99999,99999,99999};
    for (int k = 0; k < n - 1; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if(cost_matrix[j]>cost_matrix[i]+weight_matrix[i][j])
                {
                    cost_matrix[j]=cost_matrix[i]+weight_matrix[i][j];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if(cost_matrix[j]>cost_matrix[i]+weight_matrix[i][j])
                {
                    printf("A negative cycle has been detected\n");
                    return 0;
                }
            }
        }
    // print cost_matrix
    printf("\nThis is the minimum cost of the path:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", cost_matrix[i]);
    }
}

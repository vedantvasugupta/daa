#include <stdio.h>
int *  fill_cost_matrix(int *cost_matrix, int *location_matrix, int *dimensions, int n);

int main()
{
    int n;
    printf("Input the number of matrixes: ");
    scanf("%d", &n);
    printf("Input the dimensions of the matrices: ");
    int *dimensions = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n + 1; i++)
    {
        scanf("%d", (dimensions + i));
    }
    // print dimensions
    for (int i = 0; i < n + 1; i++)
    {
        printf("%d ", *(dimensions + i));
    }
    printf("Successfully saved matrices' dimensions \n");
    int *cost_matrix = malloc(sizeof(int *) * n * n);
    for (int i = 0; i < n; i++)
    {
        *(cost_matrix + i * n + i) = 0;
    }
    printf("Successfully allocated cost matrix \n");
    int *location_matrix = malloc(sizeof(int) * n * n);
    printf("Trying to fill the cost matrice\n ");
    cost_matrix = fill_cost_matrix(cost_matrix, location_matrix, dimensions, n);
}

int *  fill_cost_matrix(int *cost_matrix, int *location_matrix, int *dimensions, int n)
{
    for (int k = 1; k < n; k++)
    {
        for (int i = 0, j = k; i < n, j < n; i++, j++)
        {
            // printf("cost_matrix[%d,%d]: ", i, j, *(cost_matrix + i * n + j));
            *(cost_matrix + i * n + j) = formula(dimensions, cost_matrix, i, j, n);
            // printf("%d ", i, j, *(cost_matrix + i * n + j));
        }
        printf("\n");
    }
    return cost_matrix; 
}

int formula(int *dimensions, int **cost_matrix, int i, int j, int n)
{
    if (j == 0)
    {
        return 0;
    }
    int min_cost = 999999;
    for (int k = i; k < j; k++)
    {
        int temp_cost = 0;
        printf("Adding %d", *(dimensions + i) * (*(dimensions + k + 1)) * (*(dimensions + j + 1)));
        temp_cost = temp_cost +  *(cost_matrix + i * n + k);
        temp_cost = temp_cost + *(cost_matrix + (k + 1) * n + j);
        temp_cost = temp_cost + *(dimensions + i) * (*(dimensions + k + 1)) * (*(dimensions + j + 1));
        printf("So in this itteration the temp cost is : %d\n", temp_cost);
        if (temp_cost < min_cost)
        {
            printf("Chaning min cost to %d\n", temp_cost);
            min_cost = temp_cost;
        }
    }
    return min_cost;
}
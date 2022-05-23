//chain matrix multiplication
#include<stdio.h>
int main()
{
    int n;      //no of matrix
    printf("Enter number of matrix - > ");
    scanf("%d", &n);

    int d[2*n]; //dimensions of n matricies
    printf("Enter the dimesions of matricies -> ");
    for(int i = 0; i<2*n; i++)
        scanf("%d", &d[i]);
    
    int dim[n+1], a = 0;

    for(int i=0; i<n+1; i++)
    {
        if(i==n)
            dim[i] = d[2*n-1];
        else
            dim[i] = d[a];
        a +=2;
    }

    // for(int i =0; i<n+1; i++)
    //     printf("dim[%d] = %d\n", i, dim[i]);


    int mc[n][n], m_k[n][n], x, y, min, min_k;

    for(int i =0 ; i < n; i++)  //assigning diagonal values to 0
        mc[i][i] = 0;
    

    int j, t=0;
    while(t!=n-1)
    { 
        for (int i = 0; i<n-1; i++) 
        {
            j = i+t+1; 
            x = 10000000;
                for(int k = i; k<j; k++) 
                {
                    if(k==i)
                    {
                        min = mc[i][k] + mc[k+1][j] + dim[i]*dim[j+1]*dim[k+1];
                        min_k = k;
                    }  
                    else 
                    {
                        x = mc[i][k] + mc[k+1][j] + dim[i]*dim[j+1]*dim[k+1]; 
                    }

                    if(min > x) 
                    {
                        min = x;
                        min_k = k;
                    }
                }
                mc[i][j] = min;
                m_k[i][j]= min_k;
        }
        t++;
    }

    // for(int i =0; i<n; i++)
    // {
    //     for(int j=0; j<n; j++)
    //     {
    //         printf("%d\t\t", m_k[i][j]);
    //     }
    //     printf("\n\n");
    // }

    int minimum = mc[0][n-1];
    printf("\nMinimum = %d\n", minimum);
    return 0;    
}

// 3
// 3 5 5 7 7 5
// 4
// 2 4 4 6 6 8 8 10

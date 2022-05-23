#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

int minimum(int a,int b,int *min) { 
    printf("a is %d b is %d\n", a,b);
    if(a < b)
        *min = 0;    
    else 
        *min = 1;
    return a < b ? a : b;        
}

void rightshift(char* string,int l,int i) {
    for(int x = i+1;x > l && x > 0;x--) {
        string[x] = string[x-1];
    }
}

void paranthesis(int **ptr,int n) {
    int i,j,l;
    char k = 'a',x;
    char string[50];
    for(i = 0;i < n-1;i++) {
        string[i] = k++;
    }
    j = n-1;
    while(ptr[1][j] > 1) {
        // printf("j is %d\n", ptr[1][j]);
        x = 'a' + (ptr[1][j] - 1);                                  //to be search
        // printf("x is %c\n", x);
        l = i;
        while(x != string[l] && l > -1) {
            l--;
        }
        // printf("%c\n", string[l]);

        rightshift(&string[0],l,i);
        string[++l] = ')';
        i++;

        // printf("\nl-ptr[1][j] %d\n", l-ptr[1][j]);                 // leftbracket at string[l-ptr[1][j]]
        rightshift(&string[0],l-ptr[1][j],i);
        i++;
        string[l-ptr[1][j]] = '(';
        j--;
    }

    for(j = 0;j < i;j++) {
        printf("%c", string[j]);
    }

}

int matrixChain(int *ptr,int **dp,int **str,int i,int j) {
    int min = 0;
    if(i == j)
        dp[i][j] = 0;
    else if(dp[i][j] != -1) {
        return dp[i][j];
    }
    else {
        dp[i][j] = INT_MAX;
        for(int k = i;k < j;k++) {
            min = 0;
            dp[i][j] = minimum(dp[i][j],matrixChain(ptr,dp,str,i,k) + matrixChain(ptr,dp,str,k+1,j) + ptr[i-1]*ptr[k]*ptr[j],&min);
            // printf("dp is %d\nk is %d\n", dp[i][j],k);
            if(min == 1) {
                str[i][j] = k;
                // printf("str is %d\n",str[i][j]);
            }    
        }
    }
    return dp[i][j];
}

int main(){
    int n,i,j;
    printf("Number of matrix: ");
    scanf("%d", &n);
    n++;

    int *matrix = (int *)malloc(n*sizeof(int));                         //array to store degree of matrices

    int **dp = (int **)malloc(n*sizeof(int *));                         //2-d array to store the min of chain multiplication
    for(i = 0;i < n;i++)
        dp[i] = (int *)malloc(n*sizeof(int));

    int **str = (int **)malloc(n*sizeof(int *));                        //2-d array to store the k value of min
    for(i = 0;i < n;i++) 
        str[i] = (int *)malloc(n*sizeof(int *));

    for(i = 0;i < n;i++){
        scanf("%d", &matrix[i]);
    }
    for(i = 0;i < n;i++) {
        for(j = 0;j < n;j++) {
            dp[i][j] = -1;
            str[i][j] = 0;
        }
    }    
    // function
    printf("\n%d\n", matrixChain(matrix,dp,str, 1, n-1));
    printf("Table of Min(C[i][j]):\n");
    for(i = 1;i < n;i++) {
        for(j = 1;j < n;j++) {
            printf("%d\t", dp[i][j]);
        }
        printf("\n");
    }    
    printf("\nK Table:\n");
    for(i = 1;i < n;i++) {
        for(j = 1;j < n;j++) {
            printf("%d\t", str[i][j]);
        }
        printf("\n");
    }    
    printf("\n");
    //printing the paranthesis
    paranthesis(str,n);
}
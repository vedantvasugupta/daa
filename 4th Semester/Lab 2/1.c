//code for binary tree and finding max and min depth


#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *left, *right;
};

int count = 1;
int min_depth = 0;

int n, found=0;
struct node *newnode(int data)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
struct node *construct(int inorder[], int start, int end, int postorder[], int *pIndex)
{
    if (start > end)
    {
        return NULL;
    }
    struct node *node = newnode(postorder[(*pIndex)--]);
    int i;
    for (i = start; i <= end; i++)
    {
        if (inorder[i] == node->data)
        {
            break;
        }
    }
    node->right = construct(inorder, i + 1, end, postorder, pIndex);
    node->left = construct(inorder, start, i - 1, postorder, pIndex);

    return node;
}
struct node *constructTree(int inorder[], int postorder[], int n)
{
    int *pIndex = &n;
    return construct(inorder, 0, n, postorder, pIndex);
}
int max(int l, int r)
{
    if (l > r)
    {
        return l;
    }
    return r;
}
int findheight(struct node *node)
{
    int right, left;
    // printf("we are at %d\n", node->data);
    if (node->right == NULL && node->left == NULL)
    {
        return 0;
    }
    if (node->right != NULL)
    {
        right = findheight(node->right);
    }
    else
    {
        right = -1;
    }
    if (node->left != NULL)
    {
        left = findheight(node->left);
    }
    else
    {
        left = -1;
    }
    return max(left, right) + 1;
}


int find_min_depth(struct node *root)
{
    int temp = 0;
    if(root == NULL)
    {
        return 0;
    }
    if(!(root->left)&&(!(root->right)))
    {
        return min_depth;
    }
    if(root->left && root->right)
    {
        temp = temp +1;
        if(find_min_depth(root->left)>find_min_depth(root->right))
        {
            return find_min_depth(root->right)+temp;
        }
        else
        {
            return find_min_depth(root->left)+temp;
        }
    }
    if(root->left)
    {
        temp = temp+1;
        return find_min_depth(root->left)+temp;
    }
    else
    {
        temp = temp+1;
        return find_min_depth(root->left)+temp;
    }

}


int find_max_depth(struct node *root)
{
    int temp = 0;
    if(root == NULL)
    {
        return 0;
    }
    if(!(root->left)&&(!(root->right)))
    {
        return temp;
    }
    if(root->left && root->right)
    {
        temp = temp +1;
        if(find_max_depth(root->left)>find_max_depth(root->right))
        {
            return find_max_depth(root->left)+temp;
        }
        else
        {
            return find_max_depth(root->right)+temp;
        }
    }
    if(root->left)
    {
        temp = temp+1;
        return find_max_depth(root->left)+temp;
    }
    else
    {
        temp = temp+1;
        return find_max_depth(root->left)+temp;
    }

}


int main(void)
{
    int search;
    scanf("%d", &n);
    int inorder[n], postorder[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &postorder[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &inorder[i]);
    }
    // scanf("%d", &search);
    struct node *root = constructTree(inorder, postorder, n - 1);
    // printf("height is: %d\n", findheight(root));
    printf("Min depth: %d\n", find_min_depth(root));
    printf("Max depth: %d\n", find_max_depth(root));
    return 0;
}

//4 8 2 5 1 6 3 7
//8 4 5 2 6 7 3 1 

// 11 5 6 10 15
// 11 6 5 15 10
//code for heap and heap sort in c
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
struct heap
{
    int value;
    struct heap *left, *right, *parent;
} * temp, *root;

int find_max(int array[], int n);
void heapify(struct heap *node, int *array, int n);
struct heap *create_heap(int *array, int n);
struct heap *find_node(struct heap *root, int value, int *array, int n);
void enqueue(struct heap **queue, struct heap *temp);
int dequeue(struct heap **queue);
void print(struct heap **queue);
void swap_array_numbers(int x, int y, int *array, int n);
void delete_node(struct heap *node);

int main()
{
    int array[] = {3,4,9,5,10,2,7,31};
    int n = sizeof(array) / sizeof(array[0]);
    clock_t t;
    // t = clock();
    int max = find_max(array, n);
    root = create_heap(&array[0], n);
    printree(root);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        struct heap *blah = find_node(root, array[n - i - 1], &array[0], n);
        printf("Finally found in main : %d ", blah->value);
        root->value = blah->value;
        blah->value = array[0];

        int x = array[0];
        array[0] = array[n - i - 1];
        array[n - i - 1] = x;
        printf("\nIntermediate sorted array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
        delete_node(blah);
        printf("\nTree after deleting the node: \n");
        printree(root);
        heapify(root, &array[0], n);
        printf("\nTree after heapifying: \n");
        printree(root);
    }
    // t = clock() - t;
    // printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
    printf("\nFinal array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

struct heap *create_heap(int *array, int n)
{
    temp = (struct heap *)malloc(sizeof(struct heap));
    struct heap **queue = (struct heap *)malloc(sizeof(struct heap) * n);
    for (int i = 0; i < n; i++)
        *(queue + i) = NULL;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            // printf("\nRoot is here.");
            temp->value = *(array + i);
            temp->parent = NULL;
            temp->left = NULL;
            temp->right = NULL;
            root = temp;
            // printf("\nAdded %d to tree", temp->value);
            enqueue(queue, temp);
        }
        else
        {
            temp = *(queue);
            // printf("\nAdding childs to %d\n", temp->value);
            struct heap *temp2 = (struct heap *)malloc(sizeof(struct heap));

            if (temp->left == NULL)
            {
                temp2->parent = temp;
                temp->left = temp2;
                temp2->value = *(array + i);
                printf("\nAdded %d to tree to the left of %d ", temp2->value, temp->value);

                temp2->left = NULL;
                temp2->right = NULL;
                enqueue(queue, temp2);
                printf("\nEnequed: %d", temp2->value);
                print(queue);
                printf("lol");
            }
            else if (temp->right == NULL)
            {
                temp2->parent = temp;
                temp->right = temp2;
                temp2->value = *(array + i);
                printf("\nAdded %d to tree to the right of %d", temp2->value, temp->value);
                temp2->left = NULL;
                temp2->right = NULL;
                enqueue(queue, temp2);
                printf("\nEnequed: %d", temp2->value);
                print(queue);
                printf("Dequed: %d ", dequeue(queue));
                print(queue);
            }
        }
    }

    // printf("%d %d", temp->value, temp->left->value);
    // printree(root);
    printf("\nTree has been created successfully\n");
    printree(root);
    printf("Now starting to create the heap: \n");
    int mid = n / 2 - 1;

    for (int i = mid; i >= 0; i--)
    {
        printf("\nFinding %d\n", *(array + i));
        struct heap *tbh = find_node(root, *(array + i), array, n);
        printf("We are now going to heepify: %d\n", tbh->value);
        // printree(tbh);
        heapify(tbh, array, n);
        // printree(root);
    }
    printf("\n\nFinal tree\n");
    printree(root);
    return root;
}
void heapify(struct heap *node, int *array, int n)
{
    // printf("%d %d\n", node->value, node->left->value);
    if (node->left != NULL && node->right != NULL)
    {
        if (node->left->value > node->right->value && node->left->value > node->value)
        {
            int x = node->left->value;
            node->left->value = node->value;
            node->value = x;

            swap_array_numbers(node->value, node->left->value, array, n);
            // printf("\nSwapped %d and %d", x, node->left->value);
            heapify(node->left, array, n);
        }
        else if (node->right->value > node->left->value && node->right->value > node->value)
        {
            int x = node->right->value;
            node->right->value = node->value;
            node->value = x;
            // printf("here");
            swap_array_numbers(node->right->value, node->value, array, n);
            heapify(node->right, array, n);
            return;
        }
        else
            return;
    }
    else if (node->left != NULL)
    {
        // printf("lol");
        if (node->left->value > node->value)
        {
            int x = node->left->value;
            node->left->value = node->value;
            node->value = x;
            swap_array_numbers(node->left->value, node->value, array, n);
            // printf("\nSwapped %d and %d", x, node->left->value);
            return;
        }
    }
    return;
}

int find_max(int array[], int n)
{
    int max = -1;
    for (int i = 0; i < n; i++)
    {
        if (max < array[i])
        {
            max = array[i];
        }
    }
    return max;
}

void enqueue(struct heap **queue, struct heap *temp)
{
    int i = 0;
    while (*(queue + i) != NULL)
    {
        i++;
    }
    *(queue + i) = temp;
}

int dequeue(struct heap **queue)
{
    if (*(queue) == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    else if (*(queue + 1) == NULL)
    {
        int blah = (*(queue))->value;
        *(queue) = NULL;
        printf("Queue had one element\n");
        return blah;
    }
    int i;
    int blah = (*(queue))->value;
    struct heap *x = *(queue);
    for (i = 0; *(queue + i + 1) != NULL; i++)
    {
        x = *(queue + i + 1);
        *(queue + i) = x;
    }
    *(queue + i) = NULL;
    return blah;
}
void print(struct heap **queue)
{
    printf("\nQueue: ");
    int i = 0;
    while (*(queue + i) != NULL)
    {
        printf("%d ", (*(queue + i))->value);
        i++;
    }
    printf("\n");
}

struct heap *find_node(struct heap *root, int value, int *array, int n)
{
    if (value == root->value)
    {
        return root;
    }
    printf("\nin the function finding: %d\n", value);
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(array + i) == value)
        {
            index = i;
        }
    }
    if (root->left != NULL && root->right != NULL)
    {
        if (root->left->value == value)
        {
            printf("\nReturning-3: %d\n", root->left->value);
            return root->left;
        }
        if (root->right->value == value)
        {
            printf("\nReturning-2: %d\n", root->right->value);

            return root->right;
        }
    }
    else if (root->left != NULL)
    {
        if (root->left->value == value)
        {
            printf("\nReturning-1: %d\n", root->left->value);

            return root->left;
        }
    }
    // int parent = (int)((float)((float)((index) / 2) - 1));
    int parent = (index + 1) / 2 - 1;
    parent = *(array + parent);
    printf("Parent of  %d is %d\n", value, parent);
    if (root->left != NULL && root->right != NULL)
    {
        if (root->left->value == parent)
        {
            if (root->left->left->value == value)
            {
                printf("\nReturning1: %d\n", root->left->left->value);

                return root->left->left;
            }
            else
            {
                printf("\nReturning2: %d\n", root->left->right->value);

                return root->left->right;
            }
        }
        if (root->right->value == parent)
        {
            if (root->right->left->value == value)
            {
                printf("\nReturning3: %d\n", root->right->left->value);

                return root->right->left;
            }
            else
            {
                printf("\nReturning4: %d\n", root->right->right->value);

                return root->right->right;
            }
        }
    }
    else if (root->left != NULL)
    {
        if (root->left->value == parent)
        {
            if (root->left->left == value)
            {
                printf("\nReturning5: %d\n", root->left->left->value);

                return root->left->left;
            }
            else
            {
                printf("\nReturning6: %d\n", root->left->right->value);

                return root->left->right;
            }
        }
    }

    printf("finding parent now");
    struct heap *x = find_node(root, parent, array, n);
    printf("\nfound parent: %d", x->value);
    if (x->left->value == value)
    {
        printf("\nReturning7: %d\n", x->left->value);
        return x->left;
    }
    else
    {
        printf("\nReturning8: %d\n", x->right->value);
        return x->right;
    }
}

void swap_array_numbers(int x, int y, int *array, int n)
{
    printf("%d %d\n", x, y);
    int idx1, idx2;
    for (int i = 0; i < n; i++)
    {
        if (*(array + i) == x)
        {
            idx1 = i;
        }
        if (*(array + i) == y)
        {
            idx2 = i;
        }
    }
    int new = *(array + idx1);
    *(array + idx1) = *(array + idx2);
    *(array + idx2) = new;
}

void printreeUtil(struct heap *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    printreeUtil(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    printreeUtil(root->left, space);
}

void printree(struct heap *root)
{
    printreeUtil(root, 0);
}

void delete_node(struct heap *node)
{
    struct heap *x = node->parent;
    if (x->left->value == node->value)
    {
        x->left = NULL;
        free(node);
        return;
    }
    else
    {
        x->right = NULL;
        free(node);
        return;
    }
}
// this code for branch bound breadth first search in c

#include <stdio.h>
#include <stdlib.h>
#define n 5


struct node
{
    int tbv[n];
    int vertex, cost;
    struct node *children[n];
    struct node *parent;
    int cost_matrix[n][n];
} * root;

struct queue
{
    struct node *data;
    struct queue *next, *prev;
} * front, *rear;

struct node *create_root(int root_cost, int * cost_matrix);
int create_children(struct node *temp, int *cost_matrix);
void sort(int *arr);
int cost_of_child(struct node *temp, int *cost_matrix);
int traverse_childrens(struct node *temp, int *cost_matrix);
int final(struct node *temp, int *cost_matrix);
int find_minimum_cost_from_children(struct node *temp);
int depth_of_node(struct node *temp);
int queue_size();
struct node *dequeue();
void enqueue(struct node *temp);
void initialize_queue(struct node *root);
void print_tree(struct node *root);

int main()
{
    int cost_matrix[n][n];
    // take input from the user for the cost matrix
    // printf("Enter the cost matrix\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         scanf("%d", &cost_matrix[i][j]);
    //     }
    // }
    int costs[n * n] = {-1, 20, 30, 10, 11, 15, -1, 16, 4, 2, 3, 5, -1, 2, 4, 19, 6, 18, -1, 3, 16, 4, 7, 16, -1};

    for (int i = 0; i < n * n; i++)
    {
        if (costs[i] != -1)
            cost_matrix[i / n][i % n] = costs[i];
        else
            cost_matrix[i / n][i % n] = 100000;
    }
    // print cost_matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", cost_matrix[i][j]);
        printf("\n");
    }
    int mins[2 * n];

    // printf("\nMins: ");
    // reduce the matrix
    for (int i = 0; i < n; i++)
    {
        int min = 1000000;
        for (int j = 0; j < n; j++)
        {
            if (cost_matrix[i][j] < min)
            {
                min = cost_matrix[i][j];
            }
        }
        // append min to mins
        mins[i] = min;
        // printf("%d ", min);
        for (int j = 0; j < n; j++)
        {
            cost_matrix[i][j] = cost_matrix[i][j] - min;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int min = 1000000;
        for (int j = 0; j < n; j++)
        {
            if (cost_matrix[j][i] < min)
            {
                min = cost_matrix[j][i];
            }
        }
        // append min to mins
        mins[i + n] = min;
        // printf("%d ", min);
        for (int j = 0; j < n; j++)
        {
            cost_matrix[j][i] = cost_matrix[j][i] - min;
        }
    }
    // printf("\n\n");
    // print cost_matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // printf("%d ", cost_matrix[i][j]);
        }
        // printf("\n");
    }
    int root_cost = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        root_cost += mins[i];
    }

    // printf("\nRoot cost: %d\n", root_cost);
    // create root
    root = create_root(root_cost, &cost_matrix);
    // printf("Root created succesfully\n");
    // create children

    create_children(root, &cost_matrix);
    // printf("Children created succesfully\n");
    // print children
    // printf("\nChildren: \n");
    for (int j = 0; j < 4; j++)
    {
        // printf("%d ", root->children[j]->vertex);
    }
    // printf("\n");
    // create_children(root, &cost_matrix);
    // printf("Children created succesfully\n");
    int answer = final(root, &cost_matrix);
    print_tree(root);
    printf("The final answer: %d\n", find_min(root));
}
struct node *create_root(int root_cost, int *cost_matrix)
{
    root = (struct node *)malloc(sizeof(struct node));
    root->vertex = 1;
    root->cost = root_cost;
    root->tbv[0] = 2;
    root->tbv[1] = 3;
    root->tbv[2] = 4;
    root->tbv[3] = 5;
    root->tbv[4] = -1;
    root->children[0] = NULL;
    root->children[1] = NULL;
    root->children[2] = NULL;
    root->children[3] = NULL;
    root->children[4] = NULL;
    root->parent = NULL;
    // copy cost_matrix to root cost_matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // root->cost_matrix[i][j] = cost_matrix[i][j];
            root->cost_matrix[i][j]=*((cost_matrix+i*n)+j);
        }
    }
    return root;
}
// create children nodes
int create_children(struct node *temp, int *cost_matrix)
{
    // printf("reached here to create children\n");
    // print temp->tbv
    sort(&(temp->tbv));
    for (int i = 0; i < n; i++)
    {
        // printf("%d ", temp->tbv[i]);
    }
    int count = 0;
    while (temp->tbv[count] != -1)
    {
        count++;
    }
    // printf("Counting done count: %d\n", count);

    int min = 1000000;
    for (int i = 0; i < count; i++)
    {
        struct node *child = (struct node *)malloc(sizeof(struct node));
        child->vertex = temp->tbv[i];
        child->parent = temp;
        temp->children[i] = child;
        // copy parents tpv to childs tbv
        for (int j = 0; j < 5; j++)
        {
            if (temp->tbv[j] != child->vertex)
                child->tbv[j] = temp->tbv[j];
            else
                child->tbv[j] = -1;
        }

        // sort the child tbv in a way that -1 is at the end
        sort(&(child->tbv));
        // print child->tbv
        // printf("Child tbv: ");
        for (int j = 0; j < n; j++)
        {
            // printf("%d ", child->tbv[j]);
        }
        for (int i = 0; i < n; i++)
        {
            child->children[i] = NULL;
        }
        // printf("Child almost created\n");
        int temp = cost_of_child(child, cost_matrix);
        if (temp < min)
            min = temp;
        // printf("Child created\n");
    }
    return min;
}

void sort(int *arr)
{
    // printf("\nArray recieved in the function: ");
    // for (int i = 0; i < n; i++)
    // {
        // printf("%d ", arr[i]);
    // }

    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int new_array[] = {-1, -1, -1, -1, -1};
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) != -1)
        {
            new_array[count] = *(arr + i);
            count++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        *(arr + i) = new_array[i];
    }

}

// calculating cost of child
int cost_of_child(struct node *temp, int *cost_matrix)
{
    printf("Calculating the cost of node %d at depth %d: ", temp->vertex, depth_of_node(temp));

    int cost = 0;
    int new_matrix[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // new_matrix[i][j] = *((cost_matrix + i * n) + j);
            new_matrix [i][j]=temp->parent->cost_matrix[i][j];
        }
    }

    int parent_vertex = temp->parent->vertex;
    int child_vertex = temp->vertex;
    // make parent_vertex's row 10000
    for (int i = 0; i < n; i++)
    {
        new_matrix[parent_vertex - 1][i] = 100000;
    }
    // make child_vertex's column 10000
    for (int i = 0; i < n; i++)
    {
        new_matrix[i][child_vertex - 1] = 100000;
    }
    new_matrix[parent_vertex - 1][child_vertex - 1] = 100000;
    new_matrix[child_vertex - 1][parent_vertex - 1] = 100000;
    int new_cost = 0;
    // find minimums in every row and columns of the new_matrix
    int mins[2 * n];
    for (int i = 0; i < n; i++)
    {
        int min = 1000000;
        for (int j = 0; j < n; j++)
        {
            if (new_matrix[j][i] < min)
            {
                min = new_matrix[j][i];
            }
        }
        // append min to mins
        if (min < 10000)
            mins[i] = min;
        else
            mins[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        int min = 1000000;
        for (int j = 0; j < n; j++)
        {
            if (new_matrix[i][j] < min)
            {
                min = new_matrix[i][j];
            }
        }
        // append min to mins
        if (min < 10000)
            mins[i + n] = min;
        else
            mins[i + n] = 0;
    }

    for (int i = 0; i < 2 * n; i++)
    {
        new_cost += mins[i];
    }
    cost = *(cost_matrix + (parent_vertex - 1) * n + child_vertex - 1) + temp->parent->cost + new_cost;
    printf("%d %d %d\n", (*(cost_matrix + (parent_vertex - 1) * n + child_vertex - 1)), temp->parent->cost, new_cost);
    temp->cost = cost;
    printf("These were the mins: ");
    for (int i = 0; i < 2 * n; i++)
    {
        printf("%d ", mins[i]);
    }
    printf("\n");
    // copy new_matrix to temp cost_matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp->cost_matrix[i][j] = new_matrix[i][j];
        }
    }
    if (temp->vertex == 5 && depth_of_node(temp) == 1)
    {
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", new_matrix[i][j]);
            }
            printf("\n");
        }
    }
}

int traverse_childrens(struct node *temp, int *cost_matrix)
{
    // printf("node vertex: %d\n", temp->vertex);
    int count = 0;
    // print the children's vertexes
    // printf("printing the childrens of the node %d: ", temp->vertex);
    for (int i = 0; i < n; i++)
    {
        if (temp->children[i] != NULL)
        {
            if (temp->children[i]->vertex == 0)
            {
                // printf("HERE IS THE ERROR\n");
                return 0;
            }
            // printf("%d ", temp->children[i]->vertex);
            count++;
        }
    }
    // printf("\n");
    count = 0;
    if (depth_of_node(temp->children[0]) != n - 1)
    {

        int min = 1000000;

        while (temp->children[count] != NULL)
        {

            // printf("Creating children of %d in the traverse childrens function\n", temp->children[count]->vertex);
            int blah = create_children(temp->children[count], cost_matrix);
            // printf("One more children done\n");
            if (blah < min)
            {
                min = blah;
            }
            count++;
        }
        return min;
    }
}

int final(struct node *temp, int *cost_matrix)
{
    // printf("\n\nNew itteration of final\n");
    if (depth_of_node(temp) >= n - 2)
    {
        int count = 0;
        int min = 1000000;
        // while (temp->children[count] != NULL)
        // {
        //     int blah = traverse_childrens(temp, cost_matrix);
        //     if (blah < min)
        //     {
        //         min = blah;
        //     }
        //     count++;
        // }
        // return min;
        int blah = cost_of_child(temp->children[0], cost_matrix);
        if (blah < min)
        {
            min = blah;
        }
        return min;
    }
    else
    {
        // printf("Not final level\n");
        int count = 0;
        while (temp->children[count] != NULL)
        {
            traverse_childrens(temp, cost_matrix);
            count++;
        }
        // printf("Created children of node\n");
        count = 0;
        while (temp->children[count] != NULL)
        {
            final(temp->children[count], cost_matrix);
            count++;
        }
    }
}

int depth_of_node(struct node *temp)
{
    int depth = 0;
    while (temp->parent != NULL)
    {
        temp = temp->parent;
        depth++;
    }
    return depth;
}

int find_minimum_cost_from_children(struct node *temp)
{
    int min = 1000000;
    int count = 0;
    while (temp->children[count] != NULL)
    {
        if (temp->children[count]->cost < min)
        {
            min = temp->children[count]->cost;
        }
        count++;
    }
    return min;
}

void print_tree(struct node *root)
{
    printf("%d %d\n", root->vertex, root->cost);
    for (int i = 0; i < 4; i++)
        printf("%d %d ", root->children[i]->vertex, root->children[i]->cost);
    printf("\n");
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%d %d ", root->children[j]->children[i]->vertex, root->children[j]->children[i]->cost);
        }
        printf("\t");
    }
    printf("\n");
    int min = 9999999;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                printf("%d %d ", root->children[j]->children[i]->children[k]->vertex, root->children[j]->children[i]->children[k]->cost);
            }
            printf("\t");
        }
        printf("\t");
    }
    printf("\n");
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 1; l++)
                {
                    if (root->children[j]->children[i]->children[k]->children[l]->cost < min)
                    {
                        min = root->children[j]->children[i]->children[k]->children[l]->cost;
                    }
                    printf("%d %d ", root->children[j]->children[i]->children[k]->children[l]->vertex, root->children[j]->children[i]->children[k]->children[l]->cost);
                }
                printf("\t");
            }
            printf("\t");
        }
        printf("\t");
    }

    printf("\n");
    printf("The minimum cost is %d\n", min);
    printf("1 4 2 5 3 node cost: %d\n", root->children[2]->children[0]->children[1]->children[0]->cost);
    printf("1 4 2 3 node cost: %d", root->children[2]->children[0]->children[0]->cost, root->children[2]->children[0]->children[1]->cost);
}

int find_min(struct node *root)
{
    initialize_queue(root);
    int min = 1000000;
    while (front != NULL)
    {
        struct node *temp = dequeue();
        if (temp->cost < min && temp->children[0] == NULL)
        {
            printf("%d\n", depth_of_node(temp));
            min = temp->cost;
        }
        for (int i = 0; i < 4; i++)
        {
            if (temp->children[i] != NULL)
            {
                enqueue(temp->children[i]);
            }
        }
        // printf("Queue size: %d\n", queue_size(front));
    }
    return min;
}

// print queue
// initialize the queue
void initialize_queue(struct node *root)
{
    front = malloc(sizeof(struct queue));
    front->data = root;
    front->next = NULL;
    rear = front;
    front->prev = NULL;
}

// enqueue the node
void enqueue(struct node *temp)
{
    if (!rear)
    {
        initialize_queue(temp);
    }
    else
    {
        struct queue *blah = malloc(sizeof(struct queue));
        rear->next = blah;
        rear->next->data = temp;
        rear->next->next = NULL;
        rear->next->prev = rear;
        rear = rear->next;
    }
}

// dequeue the node
struct node *dequeue()
{
    struct node *temp = front->data;
    if (front->next)
        front = front->next;
    else
    {
        front = NULL;
        rear = NULL;
    }
    return temp;
}

// queue size
int queue_size()
{
    int count = 0;
    struct queue *temp = front;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}



// code for b tree in c
#include <stdio.h>
#include <stdlib.h>

struct node *split_node(struct node *node);
void inorder(struct node *node);
int get_blank(struct node *node);
struct node *get_sibling(struct node *node);

struct node
{
    struct element
    {
        int data;
        struct node *left, *right;
    } array[4];
    struct node *parent;
} * root;

int is_full(struct node *node)
{
    for (int i = 0; i < 3; i++)
    {
        if (node->array[i].data == -1)
            return 0;
    }
    return 1;
}
int if_child(struct node *node)
{
    if (node->array[0].left || node->array[0].right)
        return 1;
    else
        return 0;
}
void sort(struct node *node)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (node->array[i].data != -1)
            count++;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1; j++)
        {
            if (node->array[j].data > node->array[j + 1].data)
            {
                struct element temp = node->array[j];
                node->array[j] = node->array[j + 1];
                node->array[j + 1] = temp;
            }
        }
    }
}
void print_node(struct node *node)
{
    for (int i = 0; i < 4; i++)
    {
        if (node->array[i].data != -1)
            printf("%d ", node->array[i].data);
        else
        {
            break;
        }
    }
    printf("\n");
}
void print_node_without_newline(struct node *node)
{
    for (int i = 0; i < 4; i++)
    {
        if (node->array[i].data != -1)
            printf("%d ", node->array[i].data);
        else
        {
            break;
        }
    }
}

struct node *insert(struct node *node, struct element element)
{
    printf("Trying to insert element %d\n", element.data);
    if (node == NULL)
    {
        struct node *temp = malloc(sizeof(struct node));
        temp->array[0].data = element.data;
        temp->array[0].left = NULL;
        temp->array[0].right = NULL;
        temp->parent = NULL;
        for (int i = 1; i < 4; i++)
        {
            temp->array[i].data = -1;
            temp->array[i].left = NULL;
            temp->array[i].right = NULL;
        }
        root = temp;
        printf("Inserting %d into root node\n", element.data);
        print_node(temp);

        return temp;
    }

    else if (if_child(node))
    {
        int nearest = 0;
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", node->array[i].data);
        }
        int count = 0;
        for (int i = 0; i < 3; i++)
        {
            if (node->array[i + 1].data == -1)
                break;
            else if (node->array[i].data > element.data)
                break;
            else
                count++;
        }
        if (element.data < node->array[count].data)
        {
            printf("Inserting %d towards left of %d ", element.data, node->array[count].data);
            insert(node->array[count].left, element);
            printf("printing the node to whose left the element has been inserted: ");
            print_node(node);
            return node;
        }
        else
        {
            printf("Inserting %d towards right of %d ", element.data, node->array[count].data);
            insert(node->array[count].right, element);
            printf("printing the node to whose right the element has been inserted: ");
            print_node(node);
            printf("The count is: %d\n", count);
            if (node->array[1].right)
                print_node(node->array[1].right);
            return node;
        }
    }
    else
    {
        if (is_full(node))
        {
            printf("The node is full and trying to insert %d\n", element.data);
            node->array[3] = element;
            sort(node);
            print_node(node);
            split_node(node);
            return node;
        }
        else
        {
            printf("Inserting into non child non full node %d\n", element.data);
            int i = 0;
            while (node->array[i].data != -1)
            {
                i++;
            }
            node->array[i] = element;
            sort(node);
            printf("printing and returning the non child non full node ");
            print_node(node);
            return node;
        }
    }
}

struct node *split_node(struct node *node)
{
    struct element node_to_go_up = node->array[1];
    printf("The node is going to be split from the element %d\n", node_to_go_up.data);
    // struct element temp_array[4] = {node->array[0], node->array[1], node->array[2], node->array[3]};
    struct node *left_node, *right_node;
    left_node = malloc(sizeof(struct node));
    right_node = malloc(sizeof(struct node));
    for (int i = 0; i < 4; i++)
    {
        left_node->array[i].data = -1;
        right_node->array[i].data = -1;
        left_node->array[i].left = NULL;
        left_node->array[i].right = NULL;
        right_node->array[i].left = NULL;
        right_node->array[i].right = NULL;
    }
    int left_count = 0, right_count = 0;
    printf("Got to here\n");

    for (int i = 0; i < 4; i++)
    {
        if (node->array[i].data < node_to_go_up.data)
        {
            left_node->array[left_count] = node->array[i];
            left_count++;
        }
        else if (node->array[i].data > node_to_go_up.data)
        {
            right_node->array[right_count] = node->array[i];
            right_count++;
        }
    }
    printf("Got to here\n");
    left_node->parent = node->parent;
    right_node->parent = node->parent;
    node_to_go_up.left = left_node;
    node_to_go_up.right = right_node;
    printf("Printing left and right nodes while splitting\n");
    print_node(left_node);
    print_node(right_node);
    if (node->parent)
    {
        printf("Root node: ");
        print_node(root);
        printf("Root node right child: ");
        print_node(root->array[0].right);
        printf("This is the parent node: ");
        print_node(node->parent);
    }
    if (node->parent)
    {
        printf("The node splitting has a parent node\n");
        int count = get_blank(node->parent);
        int flag = is_full(node->parent);
        node->parent->array[count] = node_to_go_up;
        sort(node->parent);
        int location = 0;
        while (node->parent->array[location].data != node_to_go_up.data)
        {
            location++;
        }
        if (location > 0 && node->parent->array[location - 1].data != -1)
        {

            print_node(left_node);
            printf("making the right child of %d equal to the left child\n", node->parent->array[location - 1].data);
            node->parent->array[location - 1].right = left_node;
            print_node(node->parent->array[location - 1].right);
            print_node(node->parent->array[location].left);
        }
        if (location < 3 && node->parent->array[location + 1].data != -1)
        {

            printf("making the left child of %d equal to the right child\n", node->parent->array[location + 1].data);

            node->parent->array[location + 1].left = right_node;
        }
        if (flag)
        {
            printf("The parent node on inserting has become full so we are gonna split the parent node\n");
            node = split_node(node->parent);
        }
        return node;
    }
    else
    {
        printf("The node splitting has no parent node\n");

        struct node *temp2 = (struct node *)malloc(sizeof(struct node));
        temp2->array[0].data = node_to_go_up.data;
        temp2->array[0].left = left_node;
        temp2->array[0].right = right_node;
        for (int i = 1; i < 4; i++)
        {
            temp2->array[i].data = -1;
            temp2->array[i].left = NULL;
            temp2->array[i].right = NULL;
        }
        root = temp2;
        root->array[0].left->parent = root;
        root->array[0].right->parent = root;
        print_node(root);

        print_node(root->array[0].left);
        print_node(root->array[0].right);
        return root;
    }
}
int main()
{
    int array[] = {5, 3, 21, 9, 1, 13, 2, 7, 10, 12, 4, 8, 19, 42, 20, 29, 56, 31, 11};
    int n = 19;
    for (int i = 0; i < n; i++)
    {
        struct element element;
        element.data = array[i];
        element.left = NULL;
        element.right = NULL;
        if (array[i] == 4)
        {
            printf("12 wala node: ");
            print_node(root->array[1].right);
            print_node(root->array[2].left);
            print_node(root->array[2].right);
        }
        insert(root, element);
    }
    printf("B tree insertion complete\n");
    printf("The inorder traversal of the b tree: ");

    inorder(root);
}

int get_blank(struct node *node)
{
    int i = 0;
    while (node->array[i].data != -1)
    {
        if (i > 3)
        {
            return -1;
        }
        i++;
    }
    return i;
}

// inorder traversal of the b tree

void inorder(struct node *root)
{
    if (root)
    {
        for (int i = 0; i < 3 && root->array[i].data != -1; i++)
        {
            if (i == 0)
                inorder(root->array[i].left);
            printf("%d ", root->array[i].data);
            inorder(root->array[i].right);
        }
    }
}
// function to delete an element in b tree
void delete (struct node *node, int data)
{
    if (node == NULL)
        return;
    else
    {
        int location = 0;
        while (node->array[location].data != data)
        {
            location++;
        }
        if (node->array[location].left == NULL && node->array[location].right == NULL)
        {
        }
    }
}
struct node *get_sibling(struct node *node)
{
    if (node->parent == NULL)
        return NULL;
    else
    {
        struct node *parent = node->parent;
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
            {
                if (parent->array[i].left == node)
                {
                    return parent->array[i].right;
                }
            }
            if (parent->array[i].right == node)
            {
                return parent->array[i].left;
            }
        }
    }
}

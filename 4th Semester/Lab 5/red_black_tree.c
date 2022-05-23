// this is a code for red black trees in c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

struct node
{
    int value;
    char colour;
    struct node *left, *right, *parent;
} * root, *temp;

void printree(struct node *root);
void printreeUtil(struct node *root, int space);
struct node *insertion(struct node *root, int value);
void fix_insertion(struct node *node);
struct node *get_uncle(struct node *node);
char get_colour(struct node *node);
int check_violation(struct node *node);
void recolour(struct node *node);
void right_rotate(struct node *node);
void left_rotate(struct node *node);
struct node *find_node(int value);
void delete (struct node *node);

int main()
{
    int n = 8;
    int array[] = {8, 18, 5, 15, 17, 25, 40, 80};
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            root = (struct node *)malloc(sizeof(struct node));
            root->value = array[i];
            root->left = NULL;
            root->right = NULL;
            root->parent = NULL;
            root->colour = 'b';
        }
        else
        {
            temp = insertion(root, array[i]);
            if (check_violation(temp) == 1)
                fix_insertion(temp);
            // printree(root);
            // sleep(0.5);
        }
    }
    // printree(root);
    // sleep(5);
    printf("The tree is final after all the insertions\n");
    printree(root);
    delete (find_node(40));
    printf("Tree after deleting 40: \n");
    printree(root);
    insertion(root, 90);
    printf("Tree after inserting 90: \n");
    printree(root);
}

struct node *insertion(struct node *root, int value)
{

    if (root->value > value)
    {
        if (root->left)
        {
            return (insertion(root->left, value));
        }
        else
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->value = value;
            temp->parent = root;
            temp->left = temp->right = NULL;
            root->left = temp;
            temp->colour = 'r';
            return temp;
        }
    }
    else
    {
        if (root->right)
        {
            return (insertion(root->right, value));
        }
        else
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->value = value;
            temp->parent = root;
            temp->left = temp->right = NULL;
            root->right = temp;
            temp->colour = 'r';
            return temp;
        }
    }
}

void fix_insertion(struct node *node)
{
    if (node->parent == NULL)
    {
        node->colour = 'b';
        return;
    }
    struct node *og_parent = node->parent;
    struct node *og_gp = NULL;
    if (node->parent->parent)
    {
        og_gp = node->parent->parent;
    }
    struct node *uncle = get_uncle(node);

    // case 2
    //uncle is red so we recolour the grandparent parent and uncle
    for (int i = 0; i < 1; i++)
    {
        if (node->colour == 'r' && node->parent->colour == 'r')
            if (get_colour(uncle) == 'r')
            {
                recolour(node->parent);
                recolour(node->parent->parent);
                recolour(uncle);
            }
            // case 3 uncle is black and a triangle is formed
            //so we do a rotation on parent in the opp direction

            else if (get_colour(uncle) == 'b')
            {
                if (node->parent->parent->left)
                {
                    if (node->parent->parent->left->left)
                    {
                        if (node->parent->parent->left->left == node)
                        {
                            struct node *parent = node->parent;
                            struct node *gp = node->parent->parent;
                            right_right_rotate(node);
                            recolour(parent);
                            recolour(gp);
                            break;
                        }
                    }
                    else if (node->parent->parent->left->right)
                    {
                        if (node->parent->parent->left->right == node)
                        {
                            left_rotate(node);
                            fix_insertion(node->left);
                            break;
                        }
                    }
                }
                if (node->parent->parent->right)
                    if (node->parent->parent->right->right)
                    {
                        if (node->parent->parent->right->right == node)
                        {
                            struct node *parent = node->parent;
                            struct node *gp = node->parent->parent;
                            left_left_rotate(node);
                            recolour(parent);
                            recolour(gp);
                            break;
                        }
                        else
                        {

                            right_rotate(node);
                            fix_insertion(node->right);
                        }
                    }
            }
    }
    if (check_violation(og_parent) == 1)
    {
        fix_insertion(og_parent);
    }

    if (check_violation(og_gp) == 1)
    {
        fix_insertion(og_gp);
        return;
    }
    return;
}
void right_right_rotate(struct node *node)
{
    //right rotation -> gp->right = node
    // parent->left= node->right
    // node->right = parent
    if (node->parent->parent->parent == NULL)
    {
        root = node->parent;
    }
    else
    {
        node->parent->parent->parent->right = node->parent;
    }
    node->parent->parent->left = node->parent->right;
    node->parent->right = node->parent->parent;
    node->parent->parent = node->parent->parent->parent;
    node->parent->right->parent = node->parent;
}

void left_left_rotate(struct node *node)
{
    if (node->parent->parent->parent == NULL)
    {
        root = node->parent;
    }
    else
    {
        node->parent->parent->parent->right = node->parent;
    }
    node->parent->parent->right = node->parent->left;
    node->parent->left = node->parent->parent;
    node->parent->parent = node->parent->parent->parent;
    node->parent->left->parent = node->parent;
}
void left_rotate(struct node *node)
{
    node->parent->parent->left = node;
    node->parent->right = node->left;
    node->left = node->parent;
    node->parent = node->parent->parent;
    node->left->parent = node;
}
void right_rotate(struct node *node)
{
    node->parent->parent->right = node;
    node->parent->left = node->right;
    node->right = node->parent;
    node->parent = node->parent->parent;
    node->right->parent = node;
}
void recolour(struct node *node)
{
    if (node->colour == 'b')
    {
        node->colour = 'r';
        return;
    }
    node->colour = 'b';
    return;
}

int check_violation(struct node *node)
{
    if (node->parent == NULL)
    {
        if (node->colour == 'r')
            return 1;
    }
    if (node->colour == 'r' && node->parent->colour == 'r')
    {
        return 1;
    }
    return 0;
}

struct node *get_uncle(struct node *node)
{
    if (node->parent->parent != NULL)
    {
        struct node *temp2 = node->parent->parent;
        if (temp2->left)
        {
            if (temp2->left == node->parent)
            {
                if (temp2->right)
                {

                    return temp2->right;
                }
                else
                {
                    return NULL;
                }
            }
        }
        if (temp2->right)
        {
            if (temp2->right == node->parent)
            {
                if (temp2->left)
                {
                    return temp2->left;
                }
                else
                {
                    return NULL;
                }
            }
        }
    }
    return NULL;
}

char get_colour(struct node *node)
{
    if (node == NULL)
        return 'b';
    else
        return node->colour;
}

void printreeUtil(struct node *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    printreeUtil(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    if(root->colour == 'r')
    {
        printf("\033[0;31m");
    }
    printf("%d (%c)\n", root->value, root->colour);
    printf("\033[0;37m");
    printreeUtil(root->left, space);
}

void printree(struct node *root)
{
    printreeUtil(root, 0);
}

// write a function to delete a node in red black trees
void delete (struct node *node)
{
    if ((node->left == NULL && node->right != NULL) || (node->right == NULL && node->left != NULL))
    {
        if (node->left)
        {
            if (node->left->colour == 'r' || node->colour == 'r' )
            {
                node->value = node->left->value;
                free(node->left);
                node->left = NULL;
                node->colour = 'b';
            }
        }
        else
        {
            if (node->right->colour == 'r' || node->colour == 'r')
            {
                node->value = node->right->value;
                free(node->right);
                node->right = NULL;
                node->colour = 'b';
            }
        }
    }
}

// write a function to find a node in bst
struct node *find_node(int value)
{
    struct node *temp = root;
    while (temp != NULL)
    {
        if (temp->value == value)
            return temp;
        else if (temp->value > value)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL;
}
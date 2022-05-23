//quick sort for linked list in c
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct node
{
    int value;
    struct node *next;
    struct node *prev;
} * temp, *temp2, *og;
struct node *new_node(struct node *node, int value);
int main()
{
    int n;
    scanf("%d", &n);
    int blah;
    og = malloc(sizeof(struct node));
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            scanf("%d", &blah);
            // new_node(og, blah);
            og->value = blah;
            og->next = NULL;
            og->prev = NULL;
            temp = og;
        }
        else
        {
            scanf("%d", &blah);
            temp = new_node(temp, blah);
        }
    }
    temp = og;

    quickSort(og, n - 1);
}

void quickSort(struct node *head, int n)
{
    // time(sleep(1));

    // printf("\nThese are thr pivot_points and heads: %d %d ", pivot_point, head);

    if (n == 0)
    {
        return;
    }
    if (n == 1)
    {
        printf("\nRecieved array of size 1: ");
        if (head->value > head->next->value)
        {
            // int temp = array[head];
            // array[head] = array[pivot_point];
            // array[pivot_point] = temp;
            int temp = head->value;
            head->value = head->next->value;
            head->next->value = temp;
        }
        return;
    }
    else
    {
        printf("\nno error here 1");
        struct node *i = head;
        struct node *j;
        printf("\nThe array recieved: ");
        for (int l = 0; l <= n; l++)
        {
            printf("%d ", i->value);
            i = i->next;
        }
        temp = head;
        for (int q = 0; q < n; q++)
        {
            temp = temp->next;
        }
        printf("\nno error here 2");
        int pivot = temp->value;
        struct node *pivot_point = temp;
        printf("\nThe pivot is %d", pivot);
        printf("\nno error here 3");

        for (i = head, j = pivot_point;;)
        {
            // time(sleep(1));

            while (i->value <= pivot)
            {
                if (i == j)
                {
                    break;
                }
                // i++;
                i = i->next;
                printf("\n i's value is %d", i->value);
                if (i->value == pivot)
                {
                    printf("\nbreaking from here1");

                    break;
                }
                else if (i == j)
                {
                    printf("%d %d", i, j);
                    printf("\nbreaking from here2");

                    break;
                }
            }
            while (j->value >= pivot)
            {
                if (i == j)
                {
                    break;
                }
                j = j->prev;
                printf("\n j's value is %d", j->value);

                if (j == head)
                {
                    printf("\nbreaking from here3");

                    j = head;
                    break;
                }
                if (i == j)
                {
                    printf("\nbreaking from here4");
                    break;
                }
            }
            if (i == j || i == pivot_point)
            {
                printf("\nbreaking from here5");
                break;
            }
            else if (j == head)
            {
                j = head;
                printf("\nbreaking from here6");
                break;
            }

            else
            {
                int temp = i->value;
                i->value = j->value;
                j->value = temp;

                printf("\nSwapping %d and %d", j->value, i->value);
            }
        }
        printf("\nno error here 4");
        printf("\nThe i and j are now %d and %d respectively", i->value, j->value);
        int temp = pivot;
        pivot_point->value = i->value;
        i->value = temp;
        printf("\nThe i and j are now %d and %d respectively", i->value, j->value);
        printf("\nThe array before recursion is: ");
        int q = 0;
        for (struct node *k = head; q <= n; q++)
        {
            printf("%d ", k->value);
            if (k->next == NULL)
            {
                break;
            }
            k = k->next;
        }
        printf("\nno error here 4");

        if (head != j)
        { // quickSort(array, head, j);

            int count = 0;
            temp2 = head;
            while (temp2 != j)
            {
                count++;
                temp2 = temp2->next;
            }
            printf("\nCase 1 going for recursion with head %d and count: %d\n", head->value, count - 1);
            quickSort(head, count - 1);
        }
        // printf("\nno error here 5");
        printf("\nleft side array sorted");
        printf("\nThe array after left side sorting: ");
        struct node *temp3 = head;
        for (int l = 0; l <= n; l++)
        {
            printf("%d ", temp3->value);
            temp3 = temp3->next;
        }

        if (i->next != NULL)
        {
            printf("yo1 pivot point is %d", pivot_point->value);
            if (i->next != pivot_point && pivot_point != head)
            {
                printf("yo2 and i is %d", i->value);
                if (pivot_point != i)
                {

                    int count = 0;
                    temp2 = i->next;
                    while (temp2 != pivot_point)
                    {
                        count++;
                        if (temp2->next == NULL)
                        {
                            printf("\nbreaking ");
                            break;
                        }
                        temp2 = temp2->next;
                    }
                    printf("\nCase 2 going for recursion with head %d and count: %d\n", i->next->value, count);
                    if (count - 1 >= 0)
                        quickSort(i->next, count);
                }
            }
        }
        printf("\nno error here 6");

        // printf("\e[1;1H\e[2J");
        printf("\nThe sorted array: ");
        temp3 = head;
        for (int l = 0; l <= n; l++)
        {
            printf("%d ", temp3->value);
            temp3 = temp3->next;
        }
        return;
    }
}
struct node *new_node(struct node *node, int value)
{
    struct node *j = (struct node *)malloc(sizeof(struct node));
    j->value = value;
    node->next = j;
    j->prev = node;
    j->next = NULL;
    return j;
}
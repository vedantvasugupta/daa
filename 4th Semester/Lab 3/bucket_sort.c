//bucket sort in c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{

    struct node *next;
    struct node *prev;
    float value;
} * prev, *temp, *repl2, *repl;

float find_min(float array[], int n);
float find_max(float array[], int n);
void quickSort(struct node *head, int n);

int main()
{
    int n = 10;
    float array[] = {35, 25, 15, 5, 14, 18, 16, 13, 17, 19};
    clock_t t;
    t = clock();
    bucket_sort(array, n);
    t = clock() - t;
    printf("\n Units of Time Taken: %f units %f seconds\n", (float)t, ((float)t) / CLOCKS_PER_SEC);
}

void bucket_sort(float array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%f ", array[i]);
    }

    printf("got here\n");
    struct node *bucket[n];
    printf("no problem in creating buckets");
    for (int i = 0; i < n; i++)
    {
        bucket[i] = NULL;
    }
    printf("no problem in creating buckets\n");
    float max= find_max(array, n);
    float min= find_min(array, n);
    printf("max and min are %f and %f respectively\n", max, min);
    float q= max-min;
    int interval = (max-min)/n+1;
    printf("interval is %d\n", interval);
    for (int i = 0; i < n; i++)
    {
        // printf("blha");
        printf("array[i] = %f", array[i]);
        int val = ((array[i]-min)/interval);
        printf(" val: %d", val);
        if (bucket[val] == NULL)
        {
            printf(" got here 4 \n");
            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            bucket[val] = new_node;
            new_node->value = array[i];
            new_node->next = NULL;
            new_node->prev = NULL;
        }
        else
        {
            printf(" got here 3\n");

            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            new_node->value = array[i];
            temp = bucket[val];
            // printf("%f",temp->value);
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = NULL;
            new_node->prev = temp;
        }
    }
    printf("got here");

    for (int i = 0; i < n; i++)
    {
        printf("loop started");
        if (bucket[i] != NULL)
        {
            printf("bucket number: %d looks like: ", i);
            struct node *temp2 = bucket[i];
            int count = 0;
            while (temp2 != NULL)
            {
                printf("%f ", temp2->value);
                temp2 = temp2->next;
                count++;
            }
            count--;
            printf("number of elements: %d\n", count);
            quickSort(bucket[i], count);
        }
        else
        {
            printf("Bucket %d is empty\n", i);
        }
    }
    printf("\ngot here lol\n");
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        temp = bucket[i];
        // printf("%f ", temp->value);
        if (temp != NULL)
        {
            temp = bucket[i];
            while (temp != NULL)
            {
                array[count] = temp->value;
                count++;
                temp = temp->next;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%f ", array[i]);
    }
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
            float repl = head->value;
            head->value = head->next->value;
            head->next->value = repl;
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
            printf("%f ", i->value);
            i = i->next;
        }
        repl = head;
        for (int q = 0; q < n; q++)
        {
            repl = repl->next;
        }
        printf("\nno error here 2");
        float pivot = repl->value;
        struct node *pivot_point = repl;
        printf("\nThe pivot is %f", pivot);
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
                printf("\n i's value is %f", i->value);
                if (i->value == pivot)
                {
                    printf("\nbreaking from here1");

                    break;
                }
                else if (i == j)
                {
                    printf("%f %f", i, j);
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
                printf("\n j's value is %f", j->value);

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
                float repl = i->value;
                i->value = j->value;
                j->value = repl;

                printf("\nSwapping %f and %f", j->value, i->value);
            }
        }
        printf("\nno error here 4");
        printf("\nThe i and j are now %f and %f respectively", i->value, j->value);
        float repl = pivot;
        pivot_point->value = i->value;
        i->value = repl;
        printf("\nThe i and j are now %f and %f respectively", i->value, j->value);
        printf("\nThe array before recursion is: ");
        int q = 0;
        for (struct node *k = head; q <= n; q++)
        {
            printf("%f ", k->value);
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
            repl2 = head;
            while (repl2 != j)
            {
                count++;
                repl2 = repl2->next;
            }
            printf("\nCase 1 going for recursion with head %f and count: %f\n", head->value, count - 1);
            quickSort(head, count - 1);
        }
        // printf("\nno error here 5");
        printf("\nleft side array sorted");
        printf("\nThe array after left side sorting: ");
        struct node *repl3 = head;
        for (int l = 0; l <= n; l++)
        {
            printf("%f ", repl3->value);
            repl3 = repl3->next;
        }

        if (i->next != NULL)
        {
            printf("yo1 pivot point is %f", pivot_point->value);
            if (i->next != pivot_point && pivot_point != head)
            {
                printf("yo2 and i is %f", i->value);
                if (pivot_point != i)
                {

                    int count = 0;
                    repl2 = i->next;
                    while (repl2 != pivot_point)
                    {
                        count++;
                        if (repl2->next == NULL)
                        {
                            printf("\nbreaking ");
                            break;
                        }
                        repl2 = repl2->next;
                    }
                    printf("\nCase 2 going for recursion with head %f and count: %f\n", i->next->value, count);
                    if (count - 1 >= 0)
                        quickSort(i->next, count);
                }
            }
        }
        printf("\nno error here 6");

        // printf("\e[1;1H\e[2J");
        printf("\nThe sorted array: ");
        repl3 = head;
        for (int l = 0; l <= n; l++)
        {
            printf("%f ", repl3->value);
            repl3 = repl3->next;
        }
        return;
    }
}

float find_max(float array[], int n)
{
    float max = -1;
    for (int i = 0; i < n; i++)
    {
        if (max < array[i])
        {
            max = array[i];
        }
    }
    return max;
}
float find_min(float array[], int n)
{
    float min=array[0];
    for (int i = 0; i < n; i++)
    {
        if (min > array[i])
        {
            min = array[i];
        }
    }
    return min;
}
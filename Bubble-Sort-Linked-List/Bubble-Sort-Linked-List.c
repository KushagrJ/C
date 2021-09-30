#include <stdio.h>
#include <stdlib.h>


struct node
{
    int x;
    struct node * next;
};

typedef struct node Node;


// Stable sort.
void bubble_sort_linked_list(Node **);


int main(void)
{

    unsigned size;
    printf("Enter the number of integers: ");
    scanf("%u", &size);

    Node * head = NULL;
    Node * current;
    Node * previous;

    printf("Enter %u integers: ", size);

    for (unsigned i = 0; i < size; i++)
    {
        current = (Node *) malloc(sizeof (Node));
        if (current == NULL)
            exit(EXIT_FAILURE);

        if (head == NULL)
            head = current;
        else
            previous->next = current;
        current->next = NULL;

        scanf("%d", &current->x);

        previous = current;
    }

    bubble_sort_linked_list(&head);

    printf("After sorting: ");
    current = head;
    while (current)
    {
        printf("%d ", current->x);
        current = current->next;
    }
    printf("\n");

    while (head)
    {
        Node * next = head->next;
        free(head);
        head = next;
    }

    return 0;

}


void bubble_sort_linked_list(Node ** ptr_head)
{

    /*

    Bubble sort for an array of integers :-

    int temp;
    for (int i = 1; i < size; i++)
        for (int j = 0; j < size-i; j++)
            if (arr[j] > arr[j+1])
                temp=arr[j], arr[j]=arr[j+1], arr[j+1]=temp;

    In this function, current and next correspond to
    arr[j] and arr[j+1], respectively.

    */

    Node * current;
    Node * previous;
    Node * next;

    Node * end_of_current_iteration = NULL;

    while (end_of_current_iteration != (*ptr_head)->next)
    {
        current = *ptr_head;
        previous = NULL;
        next = (*ptr_head)->next;

        while (next != end_of_current_iteration)
        {
            if (current->x > next->x)
            {
                if (previous == NULL) // i.e. 0th & 1st nodes
                    *ptr_head = next; // are to be swapped.
                else
                    previous->next = next;
                current->next = next->next;
                next->next = current;

                // To swap the addresses stored in current
                // and next.
                current = next;
                next = next->next;
            }

            previous = current;
            current = next;
            next = next->next;
        }

        end_of_current_iteration = current;
    }

}

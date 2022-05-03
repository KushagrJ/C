#include <stdio.h>
#include <stdlib.h>


struct node
{
    int num;
    struct node* next;
};

typedef struct node Node;


void merge_sort_singly_linked_list(Node**);


int main(void)
{

    Node* head = NULL;

    Node* current;
    Node* previous;

    int num;
    printf("Enter integers (q to quit): ");

    while (scanf("%d", &num) == 1)
    {
        current = (Node*) malloc(sizeof (Node));
        current->num = num;

        if (head == NULL)
            head = current;
        else
            previous->next = current;
        current->next = NULL;

        previous = current;
    }

    if (head)
    {
        printf("Integers entered: ");
        current = head;
        while (current)
        {
            printf("%d ", current->num);
            current = current->next;
        }
        putchar('\n');
    }

    while (head)
    {
        Node* temp = head->next;
        free(head);
        head = temp;
    }

    return 0;

}


void merge_sort_singly_linked_list(Node** ptr_head
{



}

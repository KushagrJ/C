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

The main function
public static Node merge_sort(Node head) 
{
    if(head == null || head.next == null) 
        return head;
        
    Node middle = getMiddle(head);      //get the middle of the list
    Node left_head = head;
    Node right_head = middle.next; 
    middle.next = null;             //split the list into two halfs

    return merge(merge_sort(left_head), merge_sort(right_head));  //recurse on that
}

//Merge subroutine to merge two sorted lists
public static Node merge(Node a, Node b)
{
    Node dummyHead = new Node();
    for(Node current  = dummyHead; a != null && b != null; current = current.next;)
    {
        if(a.data <= b.data) 
        {
            current.next = a; 
            a = a.next; 
        }
        else
        { 
            current.next = b;
            b = b.next; 
        }
        
    }
    dummyHead.next = (a == null) ? b : a;
    return dummyHead.next;
}

//Finding the middle element of the list for splitting
public static Node getMiddle(Node head)
{
    if(head == null) 
        return head;
    
    Node slow = head, fast = head;
    
    while(fast.next != null && fast.next.next != null)
    {
        slow = slow.next;
        fast = fast.next.next;
    }
    return slow;
}

}

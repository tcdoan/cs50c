#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int num;
    struct node *next;
};

void print_list(struct node *head)
{
    for (struct node *x = head; x != NULL; x = x->next)
    {
        printf(" -> %d", x->num);
    }
    printf("\n");
}

struct node* insert (struct node *head, int num)
{
    struct node *n = malloc(sizeof(struct node));
    n->next = NULL;
    n->num = num;

    if (head == NULL)
    {
        head = n;
        return head;
    }

    if (num < 6) 
    {
        n->next = head;
        head = n;
    } 
    else if (num == 6) 
    {
        // find 4
        for (struct node *x = head; x != NULL; x = x->next)
        {
            if (x->num == 4)
            {
                n->next = x->next;
                x->next = n;
            }
        }
    }
    return head;
}

int main() 
{
    struct node* head = NULL;
    for (int i = 1; i <=6; i++)
    {
        head = insert(head, i);
    }
    print_list(head);
}

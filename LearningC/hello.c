#include <stdio.h>
#include <stdlib.h>
#include <string.h>        

#define SWAP(a, b) (a += b, b = a-b, a -= b)
struct node {
    int num;
    struct node *next;
};


struct node *add_node(struct node* head, int val)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->next = head;
    p->num = val;
    head = p;
    return head;
}

struct node *opp_node(struct node* head)
{
    struct node *p, *q, *t;
    p = head;
    q = head->next;
    p->next = NULL;
    while (q != NULL) {
        t = p;
        p = q;
        q = p->next;
        p->next = t;    
    }
    head = p;
    return head;
}

void display_node(struct node* head)
{
    struct node* p;
    p = head;
    while (p != NULL) {
        printf("-->: %d\n", p->num);
        p = p->next;
    }
}

int main()
{
    struct node* head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;

    int i;
    for (i = 1; i < 10; i++) {
        head = add_node(head, i);
    } 
    display_node(head);
    head = opp_node(head);
    display_node(head);
}

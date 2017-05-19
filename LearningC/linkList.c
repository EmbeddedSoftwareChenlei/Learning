#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    struct node* next;
};

struct node* head = NULL;

void cre_list()
{
    head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;
}

void add_node(int num)
{
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->num = num;
    ptr->next = head;
    head = ptr;
}

void add_five_node(int num)
{
    int i = 0;
    struct node *p, *q;
    p = head;
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->num = num;
    while((p->num)!=5) {
        p = p->next;
    }
    ptr->next = p->next;
}

struct node *opp_node(struct node *head)
{
    struct node *p, *front, *q;
    front = NULL;
    p = head;
    while(p!=NULL) {
        q = p->next;
        p->next = front;
        front = p;
        p = q;
    }
    head = front;
    return head;
}

void display_node()
{
    struct node *p = head;
    do {
        printf("%d\t", p->num);
        p = p->next;
    } while(p!=NULL);
    printf("\n");
}

void delete_node()
{
    struct node *p, *q;
    p = head;
    q = head->next;
    while(q!=NULL) {
        if ((q->num)%2 == 0) {
            p->next = q->next;
            free(q);
            q = p->next;
            continue;
        }
        p = p->next;
        q = q->next;
    }
    if ((head->num)%2 == 0) {
        p = head;
        head = head->next;
        free(p);
        p = NULL;
    }
}

int main()
{
    int i = 0;
    cre_list();
    for (i; i< 10; i++) {
        add_node(i);
    }
    display_node();
    //add_five_node(12);
    display_node();
    delete_node();
    display_node();
    head = opp_node(head);
    display_node();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node  {
    int num;
    struct Node* next; 
};

void display_node(struct Node* ptr)
{
    struct Node* p = ptr;
    do {
        printf("%d\t", p->num);
        p = p->next;
    } while(p != NULL);
    printf("\n");
}

struct Node* add_node(struct Node* head, int num)
{
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    ptr->num = num;
    ptr->next = head;
    head = ptr;
    return head;
}

struct Node* opp_node(struct Node* head)
{
    struct Node* p, * front, * q;
    p = head;
    q = head->next;
    head->next = NULL;
    while(q != NULL) {
        front = q->next;
        q->next = p;
        p = q;
        q = front;
    }
    head = p;
    return head;
}

int main()
{
/*
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    int i = 1;
    for (i = 1; i < 10; i++) {
        head = add_node(head, i);
    }
    display_node(head);
    head = opp_node(head);
    display_node(head);
*/
    int **p;
    p = (int **)malloc(sizeof(int *));
    printf("size=%d\n", sizeof(p));
    int i, j;
    for (i = 0; i < 4; i++) {
    *(p+i) = (int *)malloc(sizeof(int));
        for (j = 0; j < 4; j++) {
            printf("*(p+i)=%p, (*(*(p+i)+j))=%p \n", p+i, (*(p+i)+j));
            //*(*(p+i)+j) = 4;
            p[i][j] = rand();
        }
    }
    for (i = 0; i < 4; i++) {
        for (j =0; j < 4; j++) {
            printf("---->: %d\n", *(*(p+i)+j));
        }
    }
}

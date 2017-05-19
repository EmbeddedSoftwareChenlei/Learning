#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binary_tree {
    int val;
    struct binary_tree* left_child;
    struct binary_tree* right_child;
};

typedef struct binary_tree node;

void insert(node** tree, int num)
{
    node* temp = NULL;
    if (!(*tree)) {
        printf("insert root num=%d\n", num);
        temp = (node *)malloc(sizeof(node));
        temp->left_child = temp->right_child = NULL;
        temp->val = num;
        *tree = temp;
        return;
    }

    if ((*tree)->val > num) {
        printf("insert left num=%d\n", num);
        insert(&((*tree)->left_child), num);
    } else {
        printf("insert right num=%d\n", num);
        insert(&((*tree)->right_child), num);
    }
}

void display_tree(node* tree)
{
    if (tree) {
        printf("dataValue ==>%d\n", tree->val);
        display_tree(tree->left_child);
        display_tree(tree->right_child); 
    }
}

void swap(int *a, int* b)
{
	int i;
    int temp;
    for (i = 0; i < 3; i++) {
        temp = *(a+i);
        *(a+i) = *(b+i);
        *(b+i) = temp;
    }
}

int main()
{
    node* tree = NULL;
    insert(&tree, 9); 
    insert(&tree, 7); 
    insert(&tree, 8); 
    insert(&tree, 6); 
    insert(&tree, 5); 
    display_tree(tree);
    //int a[3] = {1, 2, 3};
    //int b[3] = {4, 5, 6};
    //swap(a, b);
    //int i;
    //for (i = 0; i < 3; i++) {
    //    printf("a --->%d\n", a[i]);
    //    printf("b --->%d\n", b[i]);
    //}
}

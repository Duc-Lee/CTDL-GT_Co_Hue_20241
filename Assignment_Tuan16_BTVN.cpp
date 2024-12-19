#include <stdio.h>
#include <stdlib.h>


typedef struct AvlNode {
    int elem;               
    struct AvlNode* left;  
    struct AvlNode* right;  
    int height;            
} AvlNode;
int height(AvlNode* t) {
    return t == NULL ? -1 : t->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Xoay trai
void rotateWithLeftChild(AvlNode** k2) {
    AvlNode* k1 = (*k2)->left;
    (*k2)->left = k1->right;
    k1->right = *k2;
    (*k2)->height = max(height((*k2)->left), height((*k2)->right)) + 1;
    k1->height = max(height(k1->left), (*k2)->height) + 1;
    *k2 = k1;
}

// Xoay phai
void rotateWithRightChild(AvlNode** k2) {
    AvlNode* k1 = (*k2)->right;
    (*k2)->right = k1->left;
    k1->left = *k2;
    (*k2)->height = max(height((*k2)->left), height((*k2)->right)) + 1;
    k1->height = max(height(k1->right), (*k2)->height) + 1;
    *k2 = k1;
}

// Xoay kep trai cay
void doubleWithLeftChild(AvlNode** k3) {
    rotateWithRightChild(&((*k3)->left));
    rotateWithLeftChild(k3);
}

// Xoay kep phai cay
void doubleWithRightChild(AvlNode** k3) {
    rotateWithLeftChild(&((*k3)->right));
    rotateWithRightChild(k3);
}

// Can bang cay
void balance(AvlNode** t) {
    if (*t == NULL) return;

    if (height((*t)->left) - height((*t)->right) > 1) {
        if (height((*t)->left->left) >= height((*t)->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    } else if (height((*t)->right) - height((*t)->left) > 1) {
        if (height((*t)->right->right) >= height((*t)->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }

    (*t)->height = max(height((*t)->left), height((*t)->right)) + 1;
}

// Chen mot gia tri vao cay
void insert(int x, AvlNode** t) {
    if (*t == NULL) {
        *t = (AvlNode*)malloc(sizeof(AvlNode));
        if (*t == NULL) {
            printf("Khong du bo nho.\n");
            return;
        }
        (*t)->elem = x;
        (*t)->left = (*t)->right = NULL;
        (*t)->height = 0;
    } else if (x < (*t)->elem) {
        insert(x, &((*t)->left));
    } else if (x > (*t)->elem) {
        insert(x, &((*t)->right));
    }
    balance(t);
}

// Duyet cay theo thu tu giua
void inorderTraversal(AvlNode* t) {
    if (t == NULL) return;
    inorderTraversal(t->left);
    printf("%d ", t->elem);
    inorderTraversal(t->right);
}

// Huy cay
void freeTree(AvlNode* t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

int main() {
    int arr[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(arr) / sizeof(arr[0]);
    AvlNode* root = NULL;
    // Chen cac phan tu vao cay avl
    for (int i = 0; i < n; i++) {
        insert(arr[i], &root);
    }
    printf("Cay AVL sau khi chen cac phan tu:\n");
    inorderTraversal(root);
    printf("\n");
    freeTree(root);
    return 0;
}

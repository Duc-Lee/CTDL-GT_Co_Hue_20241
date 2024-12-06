#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Dinh nghia
typedef struct Node {
    char data[10];          
    struct Node* left;      
    struct Node* right;     
} Node;

// Tao node moi
Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Kiem tra toan tu
int Toan_tu(char* c) {
    return strcmp(c, "+") == 0 || strcmp(c, "-") == 0 || strcmp(c, "*") == 0 || strcmp(c, "/") == 0 || strcmp(c, "^") == 0;
}

// Kiem tra cay rong
int isTreeEmpty(Node* root) {
    return root == NULL;
}

// Tao cay tu bieu thuc
Node* buildExpressionTree(char Hau_to[][10], int n) {
    Node* stack[100];
    int top = -1;
    for (int i = 0; i < n; i++) {
        if (!Toan_tu(Hau_to[i])) {
            stack[++top] = createNode(Hau_to[i]);  
        } else {
            Node* Node_toan_tu = createNode(Hau_to[i]);  
            Node_toan_tu->right = stack[top--];          
            Node_toan_tu->left = stack[top--];           
            stack[++top] = Node_toan_tu;                 
        }
    }
    return stack[top];
}
// Trung to
void Ham_trung_to(Node* root) {
    if (root == NULL) return;  
    Ham_trung_to(root->left);
    printf("%s ", root->data);
    Ham_trung_to(root->right);
}

// Hau to
void Ham_hau_to(Node* root) {
    if (root == NULL) return; 
    Ham_hau_to(root->left);
    Ham_hau_to(root->right);
    printf("%s ", root->data);
}

// Tien to
void Ham_tien_to(Node* root) {
    if (root == NULL) return;  
    printf("%s ", root->data);
    Ham_tien_to(root->left);
    Ham_tien_to(root->right);
}
int main() {
    // Bieu thuc hau to : (a*5-b*c^6/d)+(h-f)*e^(1/2)
    char tp_hau_to[][10] = {"a", "5", "*", "b", "c", "6", "^", "*", "d", "/", "-", 
                          "h", "f", "-", "e", "1", "2", "/", "^", "*", "+"};
    int n = sizeof(tp_hau_to) / sizeof(tp_hau_to[0]);
    // Tao cay bieu thuc
    Node* root = buildExpressionTree(tp_hau_to, n);
    if (isTreeEmpty(root)) {
        printf("Cay rong!\n");
    } else {
        printf("Bieu thuc trung to: ");
        Ham_trung_to(root);
        printf("\n");
        printf("Bieu thuc hau to: ");
        Ham_hau_to(root);
        printf("\n");
        printf("Bieu thuc tien to: ");
        Ham_tien_to(root);
        printf("\n");
    }
    return 0;
}

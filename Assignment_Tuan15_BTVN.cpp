#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;            
    struct Node* left;    
    struct Node* right;   
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Tao cay
Node* buildTree() {
    // Goc A
    Node* root = createNode('A');
    // Con A
    root->left = createNode('B');           
    root->left->right = createNode('C');   
    // Con B
    root->left->left = createNode('D');     
    root->left->left->right = createNode('E'); 
    root->left->left->right->left = createNode('H'); 
    root->left->left->right->right = createNode('I'); 
    // Con C
    root->left->right->left = createNode('F');   
    root->left->right->right = createNode('G');  
    // Con G
    root->left->right->right->left = createNode('J'); 
    root->left->right->right->left->left = createNode('K'); 
    return root;
}

// Ham duyet cay theo thu tu truoc
void Duyet_cay_theo_tt_truoc(Node* root) {
    if (root == NULL) return;

    printf("%c ", root->data);  
    Duyet_cay_theo_tt_truoc(root->left);  
    Duyet_cay_theo_tt_truoc(root->right); 
}

// Ham duyet cay theo thu tu giua
void Duyet_cay_theo_tt_giua(Node* root) {
    if (root == NULL) return;

    Duyet_cay_theo_tt_giua(root->left);  
    printf("%c ", root->data);    
    Duyet_cay_theo_tt_giua(root->right); 
}

// Ham duyet cay theo thu tu sau
void Duyet_cay_theo_tt_sau(Node* root) {
    if (root == NULL) return;
    Duyet_cay_theo_tt_sau(root->left);  
    Duyet_cay_theo_tt_sau(root->right); 
    printf("%c ", root->data);      
}

// Ham huy cay giai phong bo nho
void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);   
    freeTree(root->right); 
    free(root);            
}

int main() {
    Node* root = buildTree();

    // In cay ra
    printf("Duyet cay theo thu tu truoc (Preorder):\n");
    Duyet_cay_theo_tt_truoc(root);
    printf("\n");

    printf("Duyet cay theo thu tu giua (Inorder):\n");
    Duyet_cay_theo_tt_giua(root);
    printf("\n");

    printf("Duyet cay theo thu tu sau (Postorder):\n");
    Duyet_cay_theo_tt_sau(root);
    printf("\n");
    freeTree(root);

    return 0;
}

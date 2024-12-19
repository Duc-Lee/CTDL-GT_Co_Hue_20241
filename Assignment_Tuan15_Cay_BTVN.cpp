#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100

typedef struct TreeNode {
    char title[MAX_TITLE_LENGTH];      // Tieu de cua chuong
    int pages;                         // So trang
    struct TreeNode* firstChild;       // Con trai
    struct TreeNode* nextSibling;      // anh em ke tiep
} TreeNode;

typedef struct {
    TreeNode* root;                    // nut goc chuong dau tien
} Tree;

// Ham khoi tao ham rong
void initializeTree(Tree* T) {
    T->root = NULL;
}

// Tao node moi
TreeNode* createNode(const char* title, int pages) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Khong du bo nho de cap phat.\n");
        exit(1);
    }
    strncpy(newNode->title, title, MAX_TITLE_LENGTH);
    newNode->pages = pages;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Ham tim node theo duong dan
TreeNode* findNode(TreeNode* root, const char* path) {
    if (root == NULL) return NULL;
    if (strcmp(root->title, path) == 0) return root;
    TreeNode* current = root->firstChild;
    while (current != NULL) {
        TreeNode* found = findNode(current, path);
        if (found != NULL) return found;
        current = current->nextSibling;
    }
    return NULL;
}

// Ham them node vao cay
void addNode(Tree* T, const char* parentPath, const char* title, int pages) {
    TreeNode* parent;
    if (parentPath == NULL || strlen(parentPath) == 0) {
        if (T->root == NULL) {
            T->root = createNode(title, pages);
            printf("Da them '%s' la goc cua cay.\n", title);
            return;
        } else {
            printf("Cay da co goc. Vui long cung cap duong dan cha.\n");
            return;
        }
    } else {
        parent = findNode(T->root, parentPath);
        if (parent == NULL) {
            printf("Khong tim thay cha '%s'.\n", parentPath);
            return;
        }
    }
    TreeNode* newNode = createNode(title, pages);
    if (parent->firstChild == NULL) {
        parent->firstChild = newNode;
    } else {
        TreeNode* sibling = parent->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = newNode;
    }
    printf("Da them '%s' vao cha '%s'.\n", title, parentPath);
}

// Ham dem so chuong
int countChapters(Tree* T) {
    if (T->root == NULL) return 0;
    int count = 0;
    TreeNode* current = T->root->firstChild;
    while (current != NULL) {
        count++;
        current = current->nextSibling;
    }
    return count;
}

// Ham tim chuong dai nhat
TreeNode* findLongestChapter(Tree* T) {
    if (T->root == NULL) return NULL;
    TreeNode* current = T->root->firstChild;
    TreeNode* longest = NULL;
    int maxPages = -1;

    while (current != NULL) {
        if (current->pages > maxPages) {
            maxPages = current->pages;
            longest = current;
        }
        current = current->nextSibling;
    }

    return longest;
}

// Ham tim node va node cha
typedef struct {
    TreeNode* parent;
    TreeNode* node;
} SearchResult;
SearchResult searchNode(TreeNode* root, const char* title, TreeNode* parent) {
    if (root == NULL) {
        SearchResult res = {NULL, NULL};
        return res;
    }
    if (strcmp(root->title, title) == 0) {
        SearchResult res = {parent, root};
        return res;
    }
    SearchResult res = searchNode(root->firstChild, title, root);
    if (res.node != NULL) return res;
    return searchNode(root->nextSibling, title, parent);
}

void deleteNode(Tree* T, const char* title) {
    if (T->root == NULL) {
        printf("Cay rong. Khong the xoa.\n");
        return;
    }
    SearchResult res = searchNode(T->root, title, NULL);
    if (res.node == NULL) {
        printf("Khong tim thay muc '%s' trong cay.\n", title);
        return;
    }
    TreeNode* nodeToDelete = res.node;
    TreeNode* parent = res.parent;
    if (nodeToDelete->firstChild != NULL) {
        TreeNode* child = nodeToDelete->firstChild;
        TreeNode* lastSibling = child;
        while (lastSibling->nextSibling != NULL) {
            lastSibling = lastSibling->nextSibling;
        }
        lastSibling->nextSibling = nodeToDelete->nextSibling;

        if (parent != NULL) {
            parent->firstChild = child;
        } else {
            T->root = child;
        }
    } else {
        if (parent != NULL) {
            TreeNode* current = parent->firstChild;
            if (current == nodeToDelete) {
                parent->firstChild = nodeToDelete->nextSibling;
            } else {
                while (current->nextSibling != NULL && current->nextSibling != nodeToDelete) {
                    current = current->nextSibling;
                }
                if (current->nextSibling == nodeToDelete) {
                    current->nextSibling = nodeToDelete->nextSibling;
                }
            }
        } else {
            T->root = NULL;
        }
    }
    printf("Da xoa muc '%s' khoi cay.\n", title);
    free(nodeToDelete);
}
void inputTree(Tree* T) {
    int n;
    printf("Nhap so luong muc trong muc luc: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char parentPath[MAX_TITLE_LENGTH];
        char title[MAX_TITLE_LENGTH];
        int pages;
        printf("Nhap duong dan cha (hoac nhan enter de them vao goc): ");
        fgets(parentPath, sizeof(parentPath), stdin);
        parentPath[strcspn(parentPath, "\n")] = 0;
        printf("Nhap tieu de muc: ");
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = 0;
        printf("Nhap so trang: ");
        scanf("%d", &pages);
        getchar();
        addNode(T, parentPath, title, pages);
    }
}

void printTree(TreeNode* root, int level) {
    if (root == NULL) return;
    for(int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("- %s (%d trang)\n", root->title, root->pages);
    printTree(root->firstChild, level + 1);
    printTree(root->nextSibling, level);
}

void printTreeFull(Tree* T) {
    if (T->root == NULL) {
        printf("Cay rong.\n");
        return;
    }
    printf("Muc Luc Cuon Sach:\n");
    printTree(T->root, 0);
}

int main() {
    Tree T;
    initializeTree(&T);
    int choice;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Nhap du lieu cho cay\n");
        printf("2. In muc luc\n");
        printf("3. Dem so chuong\n");
        printf("4. Tim chuong dai nhat\n");
        printf("5. Xoa mot muc luc\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Loai bo ky tu '\n' con lai trong stdin
        switch (choice) {
            case 1:
                inputTree(&T);
                break;
            case 2:
                printTreeFull(&T);
                break;
            case 3: {
                int chapters = countChapters(&T);
                printf("So chuong trong cuon sach: %d\n", chapters);
                break;
            }
            case 4: {
                TreeNode* longest = findLongestChapter(&T);
                if (longest != NULL) {
                    printf("Chuong dai nhat la: '%s' (%d trang)\n", longest->title, longest->pages);
                } else {
                    printf("Khong co chuong nao trong cay.\n");
                }
                break;
            }
            case 5: {
                char title[MAX_TITLE_LENGTH];
                printf("Nhap tieu de muc can xoa: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // Loai bo ky tu '\n'
                deleteNode(&T, title);
                break;
            }
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai bao cau truc danh sach lien ket don
typedef struct Node {
    char fileName[100];
    int size;
    char createdAt[20];
    struct Node* next;
} Node;

typedef struct {
    Node* firstNode;
} List;

void List_Init(List* list) {
    list->firstNode = NULL;
}

// Them file theo thu tu time
void List_Add(List* list, const char* fileName, int size, const char* createdAt) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->fileName, fileName);
    newNode->size = size;
    strcpy(newNode->createdAt, createdAt);
    newNode->next = NULL;
    // DS rong
    if (list->firstNode == NULL) {
        list->firstNode = newNode;
        return;
    }
    // chen vao dau danh sach
    if (strcmp(newNode->createdAt, list->firstNode->createdAt) < 0) {
        newNode->next = list->firstNode;
        list->firstNode = newNode;
        return;
    }
    // chen vao cuoi va giua danh sach
    Node* current = list->firstNode;
    while (current->next != NULL && strcmp(current->next->createdAt, newNode->createdAt) < 0) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
// tinh tong khich thuoc file
int Tong_size(List* list) {
    int totalSize = 0;
    Node* current = list->firstNode;
    while (current != NULL) {
        totalSize += current->size;
        current = current->next;
    }
    return totalSize;
}
// Hoan doi du lieuu hai node
void SwapNodes(Node* a, Node* b) {
    char tempFileName[100];
    int tempSize;
    char tempCreatedAt[20];
    // swap ten file
    strcpy(tempFileName, a->fileName);
    strcpy(a->fileName, b->fileName);
    strcpy(b->fileName, tempFileName);
    // swap kich thuoc file
    tempSize = a->size;
    a->size = b->size;
    b->size = tempSize;
    // swap time tao file
    strcpy(tempCreatedAt, a->createdAt);
    strcpy(a->createdAt, b->createdAt);
    strcpy(b->createdAt, tempCreatedAt);
}
// Sap xep kich thuoc file theo thu tu tang dan
void SortBySize(List* list) {
    if (list->firstNode == NULL || list->firstNode->next == NULL) return;
    Node* i = list->firstNode;
    while (i != NULL) {
        Node* j = i->next;
        while (j != NULL) {
            if (i->size > j->size) {
                SwapNodes(i, j);
            }
            j = j->next;
        }
        i = i->next;
    }
}
// loai bo file dau tien
void List_RemoveFirst(List* list) {
    if (list->firstNode == NULL) return;
    Node* obsoleteNode = list->firstNode;
    list->firstNode = list->firstNode->next;
    free(obsoleteNode);
}
// dung luong <= maxSize
void max_32gb_usb(List* list, int maxSize) {
    SortBySize(list);
    while (Tong_size(list) > maxSize) {
        List_RemoveFirst(list);
    }
}
// in ra ds
void ds_list(List* list) {
    Node* current = list->firstNode;
    printf("Danh sach cac file trong thu muc:\n");
    while (current != NULL) {
        printf("- %s (%d MB, tao luc %s)\n", current->fileName, current->size, current->createdAt);
        current = current->next;
    }
    printf("\n");
}
// giai phong bo nho
void FreeList(List* list) {
    Node* current = list->firstNode;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->firstNode = NULL;
}
int main() {
    List leduc;
    List_Init(&leduc);
    // Them cac file vao danh sach
    List_Add(&leduc, "File1.txt", 500, "2024-11-17 10:00:00");
    List_Add(&leduc, "File2.txt", 200, "2024-11-17 09:30:00");
    List_Add(&leduc, "File3.txt", 300, "2024-11-17 11:00:00");
    List_Add(&leduc, "File4.txt", 700, "2024-11-17 08:45:00");
    List_Add(&leduc, "File5.txt", 50, "2024-11-18 12:00:00");
    // In danh sach ban dau
    printf("danh sach ban dau:\n");
    ds_list(&leduc);
    printf("Tong kich thuoc file: %d MB\n", Tong_size(&leduc));
    printf("\nKhong vuot qua 32GB:\n");
    max_32gb_usb(&leduc, 32 * 1024);
    ds_list(&leduc);
    FreeList(&leduc);
    return 0;
}

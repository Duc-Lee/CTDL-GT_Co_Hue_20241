#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Cau truc node
typedef struct Node {
    char word[100]; 
    struct Node* next; 
} Node;
typedef struct {
    Node* firstNode;
} List;
void List_Init(List* list) {
    list->firstNode = NULL;
}
// them node
void List_Add(List* list, const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    // TH danh sach rong
    if (list->firstNode == NULL) {
        list->firstNode = newNode;
        return;
    }
    // chen node vao cuoi danh sach
    Node* current = list->firstNode;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}
// So sanh 2 chuoi
int Chuoikitu(const char* word1, const char* word2) {
    return strcmp(word1, word2); 
}
// Tu xuat hien nhieu nhat
char* Tu_xuat_hien_nhieu_nhat(List* list) {
    Node* current = list->firstNode;
    char* Tu_xh = NULL;
    int cnt = 0;
    // duyet qua danh sach de dem tan suat cac tu 
    while (current != NULL) {
        Node* temp = list->firstNode;
        int count = 0;
        while (temp != NULL) {
            if (Chuoikitu(current->word, temp->word) == 0) {
                count++;
            }
            temp = temp->next;
        }
        if (count > cnt) {
            cnt = count;
            Tu_xh = current->word;
        }
        current = current->next;
    }
    return Tu_xh;
}
// Loai bo tu lay
void Tu_lay(List* list) {
    Node* current = list->firstNode;
    while (current != NULL && current->next != NULL) {
        if (Chuoikitu(current->word, current->next->word) == 0) {
            Node* toDelete = current->next;
            current->next = current->next->next;
            free(toDelete);
        } else {
            current = current->next;
        }
    }
}
// Dem so luong tu duy nhat
int So_tu_duy_nhat(List* list) {
    Node* current = list->firstNode;
    int count = 0;
    while (current != NULL) {
        Node* temp = list->firstNode;
        int tu_duy_nhat = 1;
        while (temp != current) {
            if (Chuoikitu(current->word, temp->word) == 0) {
                tu_duy_nhat = 0;
                break;
            }
            temp = temp->next;
        }
        if (tu_duy_nhat) {
            count++;
        }
        current = current->next;
    }
    return count;
}
// Hien thi danh sach cac tu
void In_ds(List* list) {
    Node* current = list->firstNode;
    printf("Danh sach cac tu:\n");
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}
// Giai phong bo nho
void freeList(List* list) {
    Node* current = list->firstNode;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->firstNode = NULL;
}
int main() {
    List list;
    List_Init(&list);
    char input[1000];
    printf("Nhap cau: ");
    fgets(input, sizeof(input), stdin);
    // Tach cac tu
    char* word = strtok(input, " \n");
    while (word != NULL) {
        // Loai bo ki tu khong mong muon (dau phay, dau cham...)
        int len = strlen(word);
        if (word[len - 1] == ',' || word[len - 1] == '.' || word[len - 1] == ';' || word[len - 1] == ':') {
            word[len - 1] = '\0';
        }
        List_Add(&list, word);
        word = strtok(NULL, " \n");
    }
    // Tim tu xuat hien nhieu nhat
    char* xh_nhieu = Tu_xuat_hien_nhieu_nhat(&list);
    printf("Tu xuat hien nhieu nhat: %s\n", xh_nhieu);
    // Loai bo tu lay
    Tu_lay(&list);
    // Dem so luong tu duy nhat
    int So_tu = So_tu_duy_nhat(&list);
    printf("So luong tu vung: %d\n", So_tu);
    In_ds(&list);
    freeList(&list);
    return 0;
}

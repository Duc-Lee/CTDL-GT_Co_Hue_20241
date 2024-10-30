#include <stdio.h>
#include <stdlib.h>
struct Node {
    float heso;
    int somu;
    struct Node* link;
};
struct ListDT {
    struct Node* first;
    struct Node* last;
};
void initDT(struct ListDT* l) {
    l->first = NULL;
    l->last = NULL;
}
struct Node* callNode(float hs, int sm) {
    if (hs == 0) return NULL; 
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));
    if (p == NULL) {
        printf("Không thể cấp phát bộ nhớ cho Node\n");
        return NULL;
    }
    p->heso = hs;
    p->somu = sm;
    p->link = NULL;
    return p;
}
void addNode(struct ListDT* lDT, struct Node* p) {
    if (lDT->first == NULL) {
        lDT->first = lDT->last = p;
    } else {
        lDT->last->link = p;
        lDT->last = p;
    }
}
void attachNode(struct ListDT* lDT, float hs, int sm) {
    struct Node* pDT = callNode(hs, sm);
    if (pDT == NULL) return;  
    addNode(lDT, pDT);
}
void taoDT(struct ListDT* lDT) {
    int n;
    float hs;
    int sm;
    printf("Nhap so luong phan tu trong da thuc : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap he so cua phan tu thu %d: ", i + 1);
        scanf("%f", &hs);
        printf("Nhap so mu cua phan tu thu %d: ", i + 1);
        scanf("%d", &sm);
        attachNode(lDT, hs, sm);  
    }
}
void printDT(struct ListDT* lDT) {
    struct Node* p = lDT->first;
    printf("f(x) = ");
    int isFirst = 1; 
    while (p != NULL) {
        if (!isFirst && p->heso > 0) {
            printf(" + ");
        }
        if (p->somu == 0) {
            printf("%.1f", p->heso);
        } else if (p->somu == 1) {
            printf("%.1fx", p->heso); 
        } else {
            printf("%.1fx^%d", p->heso, p->somu); 
        }
        p = p->link;
        isFirst = 0;
    }
    printf("\n");
}
void freeDT(struct ListDT* lDT) {
    struct Node* p = lDT->first;
    while (p != NULL) {
        struct Node* temp = p;
        p = p->link;
        free(temp);
    }
    lDT->first = lDT->last = NULL;
}
int main() {
    struct ListDT lDT;
    initDT(&lDT);
    taoDT(&lDT);
    printf("Da thuc vua nhap la:\n");
    printDT(&lDT);
    freeDT(&lDT);
    return 0;
}

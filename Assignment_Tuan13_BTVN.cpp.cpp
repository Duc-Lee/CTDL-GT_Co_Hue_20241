#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

// Dinh nghia cau truc node
typedef struct Node {
    char Ten_san_pham[50]; 
    int So_san_pham;         
    double Gia_tien;         
    struct Node* next;    
} Node;
// Dinh nghia cau truc Queue
typedef struct Queue {
    Node* front; 
    Node* rear;  
} Queue;

// Tao hang doi rong
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Kiem tra hang doi co phai rong khong
int isEmptyQueue(Queue* q) {
    return q->front == NULL;
}

// them mot gio hang vao hang doi 
void enqueue(Queue* q, char* Ten_san_pham, int So_san_pham, double Gia_tien) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->Ten_san_pham, Ten_san_pham);
    newNode->So_san_pham = So_san_pham;
    newNode->Gia_tien = Gia_tien;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Xoa mot gio hang vao hang doi 
Node* dequeue(Queue* q) {
    if (isEmptyQueue(q)) return NULL;
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

// Giai phong bo nho ma da xoa hang doi 
void freeQueue(Queue* q) {
    Node* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}
int main() {
    Queue q;
    initQueue(&q);
    // thong tin cac gio hang va hang doi 
    enqueue(&q, "san pham A", 3, 10.5);
    enqueue(&q, "san pham B", 5, 2.0);
    enqueue(&q, "san pham A", 2, 10.5);
    enqueue(&q, "san pham C", 4, 3.5);
    // Tinh tong so tien va san pham A
    double Tong_thu_nhap = 0.0;
    int San_pham_A_da_ban = 0;
    printf("Bat dau thanh toan:\n");
    while (!isEmptyQueue(&q)) {
        Node* current = dequeue(&q);
        // Thong tin thanh toan
        printf("- Thanh toan gio hang: %s, So luong: %d, Tong tien: %.2f\n",
               current->Ten_san_pham, current->So_san_pham, current->So_san_pham * current->Gia_tien);

        // Cong doanh thu va kiem tra san pham A
        Tong_thu_nhap += current->So_san_pham * current->Gia_tien;
        if (strcmp(current->Ten_san_pham, "A") == 0) {
            San_pham_A_da_ban += current->So_san_pham;
        }
        free(current); 
    }
    printf("\nTong tien thu ngan thu duoc: %.2f\n", Tong_thu_nhap);
    printf("Tong so luong san pham A ban duoc: %d\n", San_pham_A_da_ban);
    return 0;
}

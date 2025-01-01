#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Khai bao do thi o dang ma tran ke
int Ma_tran_ke[MAX][MAX];
int visited[MAX];
//So dinh
int n; 

// Dsach
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* Dsach_ke[MAX];
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Tao ma tran ke
void initializeMatrix() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Ma_tran_ke[i][j] = 0;
}

// Khởi tạo danh sách kề
void initializeList() {
    for (int i = 0; i < n; i++)
        Dsach_ke[i] = NULL;
}

// Them canh vao ma tran
void addEdgeMatrix(int u, int v) {
    Ma_tran_ke[u][v] = 1;
    Ma_tran_ke[v][u] = 1; 
}

// Them canh
void addEdgeList(int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = Dsach_ke[u];
    Dsach_ke[u] = newNode;
    newNode = createNode(u);
    newNode->next = Dsach_ke[v];
    Dsach_ke[v] = newNode;
}

// In ra 
void Xuat() {
    printf("Ma tran ke:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", Ma_tran_ke[i][j]);
        }
        printf("\n");
    }
}
void Xuat_ds() {
    printf("Danh sach ke:\n");
    for (int i = 0; i < n; i++) {
        printf("Dinh %d:", i);
        Node* temp = Dsach_ke[i];
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Bfs theo chieu rong
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("BFS: ");
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (Ma_tran_ke[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// Dfs theo chieu sau
void DFS(int start) {
    printf("%d ", start);
    visited[start] = 1;

    for (int i = 0; i < n; i++) {
        if (Ma_tran_ke[start][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    int edges, u, v, start;
    printf("Nhap so dinh: ");
    scanf("%d", &n);
    initializeMatrix();
    printf("Nhap so canh: ");
    scanf("%d", &edges);
    printf("Nhap cac canh (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdgeMatrix(u, v);
        addEdgeList(u, v);
    }
    Xuat();
    Xuat_ds();
    printf("Nhap dinh bat dau cho BFS: ");
    scanf("%d", &start);
    BFS(start);
    for (int i = 0; i < n; i++) visited[i] = 0; 
    printf("Nhap dinh bat dau cho DFS: ");
    scanf("%d", &start);
    printf("DFS: ");
    DFS(start);
    printf("\n");
    return 0;
}

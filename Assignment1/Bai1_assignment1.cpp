#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

void Insertionsort(int* a, const char** a2, int n) {
    for (int i = 1; i < n; i++) {
        int last = a[i];
        const char* last2 = a2[i];  
        int j = i;
        while (j > 0 && a[j - 1] > last) {
            a[j] = a[j - 1];
            a2[j] = a2[j - 1];
            j--;
        }
        a[j] = last;
        a2[j] = last2;
    }
}

void SapXep(const char* mang[], int n) {
    int* Arrtemp = (int*)malloc(n * sizeof(int));
    if (Arrtemp == NULL) {
    	printf("khong cap phat duoc bo nho");
        return ;
    }

    for (int i = 0; i < n; i++) {
        if (strcmp(mang[i], "do") == 0) {
            Arrtemp[i] = 0;  
        } else if (strcmp(mang[i], "trang") == 0) {
            Arrtemp[i] = 1;  
        } else if (strcmp(mang[i], "xanh") == 0) {
            Arrtemp[i] = 2; 
        }
    }

    Insertionsort(Arrtemp, mang, n);

    free(Arrtemp);  
}

int main() {
    const char* colors[] = {"xanh", "do", "trang", "do", "xanh", "trang"};
    int n = sizeof(colors) / sizeof(colors[0]);

    SapXep(colors, n);

    printf("Mang sau khi sap xep la:\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", colors[i]);
    }

    return 0;
}

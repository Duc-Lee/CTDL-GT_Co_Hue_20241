//-------------------------------------MÃ GIẢ------------------------------------------------
//Function nt(int n)
//{	int i = 2;
//	if(n < 2){
//		return 0;
//	else if{
//		for i = 2 to sqrt(n) do 
//			if(n%i == 0)
//				return 0;
//	}
//	return 1;
// }
// Function ntBlum(int n)
// {
//	if(nt(n) && n%4 == 3){
//		return 1;
//	}
//	return 0;
// }
// Function CheckBlum(int n)
// {
//	int p ;
//	for p = 2 to sqrt(n) do :
//		if(n%p == 0) 
//			int q = n/p;
//		if(ntBlum(p) && ntBlum(q) && p!=q)
//			return 1;
//	return 0;
// }
// procedure FindBlum(int n)
// {
// 	int a[n];
//	int size = 0;
//	int check = 0;
//	forint i = 0 to n do :
//		if(CheckBlum(n)){
//			a[size] = i;
//			size++;
//		}
//
//	for int j = 0 to size - 1 do : 
//		for int m = j + 1 to size do :
//			if(CheckBlum(a[i] + a[j]) && a[i] + a[j] <= n){
//				printf("Cap so co tong la Blum la : %d %d\n", a[i], a[j]);
//			}
//		}
//
//	for int e = 0 to size {
//		if(m == a[e]){
//			check = 1;
//			break;
//		}
//	}
//	if(check) printf("So co trong day");
//	else printf("So khong co trong day");
// }

/// Code bang C
#include <stdio.h>
#include <math.h>

int nt(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int ntBlum(int n) {
    if (nt(n) && n % 4 == 3) {
        return 1;
    }
    return 0;
}

int CheckBlum(int n) {
    for (int p = 2; p <= sqrt(n); p++) {
        if (n % p == 0) {
            int q = n / p;
            if (ntBlum(p) && ntBlum(q) && p != q) {
                return 1;
            }
        }
    }
    return 0;
}

void FindBlum(int n, int m) {
    int a[n];  
    int size = 0;
    int found = 0;

    for (int i = 2; i <= n; i++) {
        if (CheckBlum(i)) {
            a[size++] = i;
        }
    }

    int foundPair = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            int sum = a[i] + a[j];
            if (CheckBlum(sum) && sum <= n) {
                printf("Cap so co tong la so Blum: %d + %d = %d\n", a[i], a[j], sum);
                foundPair = 1;
            }
        }
    }

    if (!foundPair) {
        printf("Khong co cap so nao co tong la so Blum\n");
    }
    for (int i = 0; i < size; i++) {
        if (m == a[i]) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("So %d co trong day so Blum\n", m);
    } else {
        printf("So %d khong co trong day so Blum\n", m);
    }
}
int main() {
    int n, m;
    printf("Nhap n va m: ");
    scanf("%d %d", &n, &m);

    FindBlum(n, m);

    return 0;
}

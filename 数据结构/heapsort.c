#include<stdio.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void build_max_heap(int a[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(&a[i], &a[largest]);
        build_max_heap(a, n, largest);
    }
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[100];
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    a[n]='\0';
    for (int i = n / 2 - 1; i >= 0; i--)
        build_max_heap(a, n, i);
        print_array(a, n);
    for(int i=0;i<2;i++){
        swap(&a[0], &a[n - 1 - i]);
        build_max_heap(a, n - 1 - i, 0);
        print_array(a, n - 1 - i);
    }
    return 0;
}

#include<stdio.h>
#include<stdlib.h> // 为了 exit()

// 全局变量，用于存储枢轴的值
int pivot_all[10000]; // 增加大小以防万一
int pivot_count = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 返回枢轴的值，并将枢轴放在 a[high]
int median_of_three(int a[], int low, int high) {
    int mid = low + (high - low) / 2;

    if (a[low] > a[mid])
        swap(&a[low], &a[mid]);
    if (a[low] > a[high])
        swap(&a[low], &a[high]);
    if (a[mid] > a[high])
        swap(&a[mid], &a[high]);

    // 将中位数（枢轴）放到 high-1 的位置，为分割做准备
    // a[high] 本身会比枢轴大，可以作为哨兵
    swap(&a[mid], &a[high - 1]); 
    return a[high - 1];
}

// 插入排序，用于处理小规模数组
void insertion_sort(int a[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int temp = a[i];
        int j = i - 1;
        while (j >= low && a[j] > temp) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

void quick_sort(int a[], int low, int high) {
    // 当数组规模较小时，切换到插入排序
    if (low + 5 > high) {
        if(low < high){
             insertion_sort(a, low, high);
        }
        return;
    }

    // 三数取中法选择枢轴
    int pivot = median_of_three(a, low, high);
    if(pivot_count < 10000) {
        pivot_all[pivot_count++] = pivot;
    }

    int i = low;
    int j = high - 1;

    // 开始分割
    while (1) {
        while (a[++i] < pivot) {}
        while (a[--j] > pivot) {}
        if (i < j) {
            swap(&a[i], &a[j]);
        } else {
            break;
        }
    }

    // 将枢轴放到正确的位置
    swap(&a[i], &a[high - 1]);

    // 递归排序左右两个子数组
    quick_sort(a, low, i - 1);
    quick_sort(a, i + 1, high);
}

int main() {
    int a[10000];
    int n = 0;
    // 修改循环条件，使其与数组容量一致
    while (n < 10000 && scanf("%d", &a[n]) == 1) {
        n++;
    }

    if (n > 0) {
        quick_sort(a, 0, n - 1);
    }

    printf("After Sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Median3 Value:\n");
    if(pivot_count == 0) {
        printf("none\n");
        return 0;
    }
    for (int i = 0; i < pivot_count; i++) {
        printf("%d ", pivot_all[i]);
    }
    printf("\n");

    return 0;
}
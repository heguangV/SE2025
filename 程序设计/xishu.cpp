#include<stdio.h>
#include<stdlib.h>

#define N 1000006

int a[N];

int search(int* a, int l, int r) {
    int sum = a[l];
    int start = l;
    int max_sum = a[l];
    for (int i = l + 1; i < r; i++) {
        if (sum < 0) {
            sum = a[i];
        } else {
            sum += a[i];
        }

        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    int mid = n >> 1;
    int left_result = search(a, 0, mid);
    int right_result = search(a, mid, n);
    int left_sum = a[mid - 1];
    int left_max = a[mid - 1];
    for (int i = mid - 2; i >= 0; i--) {
        left_sum += a[i];
        left_max = max(left_max, left_sum);
    }  
    int right_sum = a[mid];
    int right_max = a[mid];
    for (int i = mid + 1; i < n; i++) {
        right_sum += a[i];
        right_max = max(right_max, right_sum);
    }
    int cross_max = left_max + right_max;
    int final_max = max(max(left_result, right_result), cross_max);
    printf("%d\n", final_max);
    return 0;
}
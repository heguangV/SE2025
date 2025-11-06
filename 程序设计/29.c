#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for INT_MAX
#include <string.h> 

typedef unsigned long long ull;

// 比较函数 for qsort
int cmp(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

int cmp_desc(const void * a, const void * b) {
    return (*(int *)b - *(int *)a); // 降序
}

int main(){
    int n;
    scanf("%d", &n);

    int *num_arr = (int *)malloc(n * sizeof(int));
    int *cost_arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &num_arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &cost_arr[i]);
    }

    qsort(num_arr, n, sizeof(int), cmp); // 升序排序 Num
    qsort(cost_arr, n, sizeof(int), cmp); // 升序排序 Cost

    // `counts` 存储所有计算出的增量
    // 动态分配，避免全局大数组
    int *counts = (int *)malloc(n * sizeof(int)); 
    int counts_size = 0;
    int *S = (int *)malloc(n * sizeof(int)); 
    int S_top = -1; // 栈顶指针，-1表示空栈
    for (int i = 0; i < n; ++i) {
        int j = i;
        while ((j + 1) < n && (long long)num_arr[j + 1] - num_arr[i] < (long long)(j + 1) - i) { // 注意类型转换防止溢出
            ++j;
        }
        int current_top_val = num_arr[i] + j - i; 
        for (int k = j; k >= i; --k) {
            while (S_top == -1 || current_top_val >= num_arr[k]) { 
                if (S_top + 1 >= n) {
                    break; 
                }
                S[++S_top] = current_top_val--;
            }
            int now = S[S_top] - num_arr[k];
            S_top--;
            if (counts_size >= n) { 
                break;
            }
            counts[counts_size++] = now;
        }
        i = j; // 跳过已处理的区间
    }
    qsort(counts, counts_size, sizeof(int), cmp_desc);
    ull total_cost = 0;
    for (int i = 0; i < counts_size; ++i) {
        total_cost = (total_cost + (ull)counts[i] * cost_arr[i]);
    }  
    printf("%llu\n", total_cost); 
    free(num_arr);
    free(cost_arr);
    free(counts);
    free(S);

    return 0;
}
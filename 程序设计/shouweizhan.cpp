#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int lower_bound_int(const int *arr, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (arr[mid] < x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

int upper_bound_int(const int *arr, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (arr[mid] <= x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

int count_soldiers(int l, int r, int* positions, int k) {
    if (k == 0) return 0;
    int L = lower_bound_int(positions, k, l);
    int R = upper_bound_int(positions, k, r);
    return R - L;
}

ll break_wall(int A, int B, int l, int r, int* positions, int k) {
    int len = r - l + 1;
    int soldier_count = count_soldiers(l, r, positions, k);
    if (soldier_count == 0) return (ll)A; // 无士兵直接返回，避免递归
    ll direct_cost = (ll)B * (ll)soldier_count * (ll)len;
    if (len == 1) {
        return direct_cost;
    }
    int mid = l + (r - l) / 2;
    ll left_cost = break_wall(A, B, l, mid, positions, k);
    ll right_cost = break_wall(A, B, mid + 1, r, positions, k);
    
    return (direct_cost < left_cost + right_cost) ? direct_cost : left_cost + right_cost;
}

int main() {
    int n, k, A, B;
    scanf("%d %d %d %d", &n, &k, &A, &B);
    int total_positions = 1 << n;  // 2^n
    int* positions = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        scanf("%d", &positions[i]);
        positions[i] -= 1; // 改为 0-based 方便与 [0, total_positions-1] 对齐
    }
    if (k > 0) qsort(positions, (size_t)k, sizeof(int), cmp_int);
    ll cost = break_wall(A, B, 0, total_positions - 1, positions, k);
    printf("%lld\n", cost);
    free(positions);
    return 0;
}
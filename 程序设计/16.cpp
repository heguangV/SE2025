#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int val_storage[1000005]; 
int tmp[1000005];   
void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

int quickselect(int* a, int m, int k) {
    int l = 0, r = m - 1;
    int idx = k - 1;
    
    while (l < r) {
        // Hoare分区
        int pivot = a[l + rand() % (r - l + 1)];
        int i = l, j = r;
        while (i <= j) {
            while (a[i] < pivot) i++;
            while (a[j] > pivot) j--;
            if (i <= j) swap(&a[i++], &a[j--]);
        }
        //... j pivot i ...
        if (idx <= j) r = j;// k 在左边
        else if (idx >= i) l = i;// k 在右边
        else return a[idx];//pivot == k
    }
    return a[l];
}

int main(void) {
    srand(time(NULL));
    int n;
    scanf("%d", &n);
    int* val = val_storage;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &val[i]);
    }
    int t; scanf("%d", &t);
    for (int qi = 0; qi < t; ++qi) {
        int tt; scanf("%d", &tt);
        if (tt == 1) {
            int p; int x; scanf("%d%d", &p, &x);
            val[p] = x;
        } else if (tt == 2) {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int m = r - l + 1;
            for (int i = 0; i < m; ++i) tmp[i] = val[l + i];
            int ans = quickselect(tmp, m, k);
            printf("%d\n", ans);
        }
    }
    return 0;
}
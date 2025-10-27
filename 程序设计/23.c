#include <stdio.h>
#include <stdlib.h>

long long Qpow(long long a, int b) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int Qsqrt(long long a, int b, int n) {
    int l = 1, r = n, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (Qpow(mid, b) >= a) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res;
}

int check(long long x, int p, int n) {
    int root = Qsqrt(x, p, n);
    return Qpow(root, p) == x;
}

int main() {
    int n;
    scanf("%d", &n);
    long long hash[3] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            hash[j] ^= Qpow(i, j + 1);
        }
    }
    for (int i = 1; i <= n - 2; ++i) {
        int x;
        scanf("%d", &x);
        for (int j = 0; j < 3; ++j) {
            hash[j] ^= Qpow(x, j + 1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int flag = 1;
        for (int j = 0; flag && j < 3; ++j) {
            long long x = hash[j] ^ Qpow(i, j + 1);
            if (!check(x, j + 1, n)) {
                flag = 0;
            }
        }
        if (flag) {
            printf("%d %lld\n", i, hash[0] ^ i);
            return 0;
        }
    }
    return 0;
}
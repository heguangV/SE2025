#include <stdio.h>

typedef long long ll;

ll Qpow(ll a, int b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = ans * a;
        if (ans > 1e9 || a > 1e9)
            return 1e9;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int getCount(int x, int n, int m) {
    int dep = 0;
    ll total = 0;
    int cur = x;
    while (cur > 1) {
        ++dep;
        total += cur;
        cur = (cur + 1) >> 1;
    }
    total += m - dep + 1;
    return total <= n;
}

int solve(int n, int m) {
    if (m + 1 > n)
        return 0;
    
    if (Qpow(2, m + 1) - 1 >= n) {
        int l = 0, r = n, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (getCount(mid, n, m)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    } else {
        return 1 << m;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%d\n", solve(n, m));
    }
    return 0;
}
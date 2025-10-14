#include <stdio.h>
typedef long long ll;
ll f[100000 + 5];
int sz = 0;

void heap_swap(ll* a, ll* b) {
    ll t = *a; *a = *b; *b = t;
}

void heap_push(ll x) {
    int i = ++sz;
    f[i] = x;
    while (i > 1 && f[i] < f[i >> 1]) {
        heap_swap(&f[i], &f[i >> 1]);
        i >>= 1;
    }
}

ll heap_pop(void) {
    ll top = f[1];
    f[1] = f[sz--];
    int i = 1;
    while (1) {
        int l = i << 1, r = l + 1, s = i;
        if (l <= sz && f[l] < f[s]) s = l;
        if (r <= sz && f[r] < f[s]) s = r;
        if (s == i) break;
        heap_swap(&f[i], &f[s]);
        i = s;
    }
    return top;
}

int main() {
    int n = 0;
    ll sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        ll x; scanf("%lld", &x);
        heap_push(x);
    }
    for (int i = 1; i < n; i++) {
        ll a = heap_pop();
        ll b = heap_pop();
        ll s = a + b;
        sum += s;
        heap_push(s);
    }
    printf("%lld\n", sum);
    return 0;
}
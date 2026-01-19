#include <stdio.h>

typedef struct {
    int r;
    int c;
    long long v;
} Triple;

int main() {
    int x1, x2, y1, y2;
    if (scanf("%d%d", &x1, &y1) != 2) {
        return 0;
    }
    int m1;
    scanf("%d", &m1);
    Triple a1[m1];
    for (int i = 0; i < m1; i++) {
        scanf("%d%d%lld", &a1[i].r, &a1[i].c, &a1[i].v);
    }

    scanf("%d%d", &x2, &y2);
    int m2;
    scanf("%d", &m2);
    Triple a2[m2];
    for (int i = 0; i < m2; i++) {
        scanf("%d%d%lld", &a2[i].r, &a2[i].c, &a2[i].v);
    }

    int x = x1, y = y2;
    if (y1 != x2 || m1 == 0 || m2 == 0) {
        printf("%d\n%d\n", x, y);
        printf("0\n");
        return 0;
    }

    int m = m1 * m2;
    Triple a[m];

    int cnt = 0;
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < m2; j++) {
            if (a1[i].c == a2[j].r) {
                int merged = 0;
                for (int k = 0; k < cnt; k++) {
                    if (a[k].r == a1[i].r && a[k].c == a2[j].c) {
                        a[k].v += a1[i].v * a2[j].v;
                        merged = 1;
                        break;
                    }
                }
                if (!merged) {
                    a[cnt].r = a1[i].r;
                    a[cnt].c = a2[j].c;
                    a[cnt].v = a1[i].v * a2[j].v;
                    cnt++;
                }
            }
        }
    }

    int out = 0;
    for (int i = 0; i < cnt; i++) {
        if (a[i].v != 0) {
            a[out++] = a[i];
        }
    }
    cnt = out;

    printf("%d\n%d\n", x, y);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d,%d,%lld\n", a[i].r, a[i].c, a[i].v);
    }
    return 0;
}
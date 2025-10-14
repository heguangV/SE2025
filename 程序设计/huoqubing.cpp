#include <stdio.h>
#include <math.h>

typedef struct { int x, y; } Pt;
Pt a[100000 + 5];

double max2(double u, double v) { return u > v ? u : v; }

double maxDist(double x, Pt* p, int n) {
    double m = 0.0;
    for (int i = 0; i < n; ++i) {
        double dx = x - (double)p[i].x;
        double dy = (double)p[i].y;
        double d = sqrt(dx*dx + dy*dy);
        if (d > m) m = d;
    }
    return m;
}

int main(void) {
    int n;
    scanf("%d", &n);
    int minx = 1000000000, maxx = -1000000000;
    for (int i = 0; i < n; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        a[i].x = x; a[i].y = y;
        if (x < minx) minx = x;
        if (x > maxx) maxx = x;
    }
    if (n == 1) { printf("%.4f\n", fabs((double)a[0].y)); return 0; }
    double l = (double)minx, r = (double)maxx;
    for (int it = 0; it < 50; ++it) { 
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        double f1 = maxDist(m1, a, n);
        double f2 = maxDist(m2, a, n);
        if (f1 > f2) l = m1; else r = m2;
    }
    double ans = maxDist((l + r) / 2.0, a, n);
    printf("%.4f\n", ans);
    return 0;
}
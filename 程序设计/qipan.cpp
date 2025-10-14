#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAXN 1024
#define MAXT ((MAXN*MAXN)/3 + 8)

int g_id = 1;//BIAN HAO
int g_board[MAXN][MAXN];

typedef struct { int id; int r; int c; } TileInfo;
TileInfo g_arr[MAXT];
int g_remap[MAXT+1];

int tileinfo_cmp(const void *a, const void *b) {
    const TileInfo *pa = (const TileInfo *)a;
    const TileInfo *pb = (const TileInfo *)b;
    if (pa->r != pb->r) return (pa->r < pb->r) ? -1 : 1;
    if (pa->c != pb->c) return (pa->c < pb->c) ? -1 : 1;
    return (pa->id < pb->id) ? -1 : ((pa->id > pb->id) ? 1 : 0);
}

void tile(int r0, int c0, int size, int mr, int mc) {
    if (size == 1) return;
    int s = size / 2;
    int mid_r = r0 + s - 1;
    int mid_c = c0 + s - 1;
    int quad = (mr < r0 + s ? 0 : 2) + (mc < c0 + s ? 0 : 1);// 0左上,1右上,2左下,3右下
    int id = g_id++;
    int tl_r = mid_r, tl_c = mid_c;     // 左上
    int tr_r = mid_r, tr_c = mid_c + 1; // 右上
    int bl_r = mid_r + 1, bl_c = mid_c;     // 左下
    int br_r = mid_r + 1, br_c = mid_c + 1; // 右下
    if (quad != 0) g_board[tl_r][tl_c] = id;//在中心放一个L
    if (quad != 1) g_board[tr_r][tr_c] = id;
    if (quad != 2) g_board[bl_r][bl_c] = id;
    if (quad != 3) g_board[br_r][br_c] = id;
    if (quad == 0) tile(r0, c0, s, mr, mc);
    else tile(r0, c0, s, tl_r, tl_c);
    if (quad == 1) tile(r0, c0 + s, s, mr, mc);
    else tile(r0, c0 + s, s, tr_r, tr_c);
    if (quad == 2) tile(r0 + s, c0, s, mr, mc);
    else tile(r0 + s, c0, s, bl_r, bl_c);
    if (quad == 3) tile(r0 + s, c0 + s, s, mr, mc);
    else tile(r0 + s, c0 + s, s, br_r, br_c);
}

int main(void) {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    int m = 1 << n;
    if (m > MAXN) return 0; // 越界保护
    // 清零使用区域
    for (int i = 0; i < m; ++i) memset(g_board[i], 0, sizeof(int) * (size_t)m);
    int mr = x - 1;
    int mc = y - 1;
    g_id = 1;
    tile(0, 0, m, mr, mc);
    int T = g_id - 1;
    if (T > 0) {
        TileInfo *arr = g_arr;
        for (int i = 0; i < T; ++i) { arr[i].id = i + 1; arr[i].r = INT_MAX; arr[i].c = INT_MAX; }
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    int v = g_board[i][j];
                    if (v > 0) {
                        int idx = v - 1;
                        if (i < arr[idx].r || (i == arr[idx].r && j < arr[idx].c)) {
                            arr[idx].r = i; arr[idx].c = j;
                        }
                    }
                }
            }
            qsort(arr, (size_t)T, sizeof(TileInfo), tileinfo_cmp);
            int *remap = g_remap;
            for (int i = 1; i <= T; ++i) remap[i] = i;
            for (int i = 0; i < T; ++i) {
                remap[arr[i].id] = i + 1;
            }
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < m; ++j) {
                    int v = g_board[i][j];
                    if (v > 0) g_board[i][j] = remap[v];
                }
            }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            int v = g_board[i][j];
            if (j) putchar(' ');
            printf("%d", v);
        }
        putchar(' ');
        putchar('\n');
    }
    return 0;
}
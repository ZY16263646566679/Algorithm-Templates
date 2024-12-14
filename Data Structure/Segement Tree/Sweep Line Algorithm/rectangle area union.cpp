// 从下到上扫描
#include <bits/stdc++.h>
using namespace std;

#define mid (l + r >> 1)
#define lp (p << 1)
#define rp (p << 1 | 1)
#define ls lp, l, mid
#define rs rp, mid, r // 注意不是 mid + 1！！

const int N = 2e4 + 5;
int tag[N]; // 标记：线段是否有效，能否用于计算宽度
double len[N], x[N]; // len：区间的宽度，x：x 坐标

struct ScanLine {
    double y; // 边的y坐标
    double lx, rx; // 边的左右x坐标
    int inout; // 入边为1，出边为-1
    bool operator<(ScanLine& l) { return y < l.y; } // 根据y坐标排序
} line[N];

void up(int p, int l, int r) {
    if (tag[p]) len[p] = x[r] - x[l];
    else if (l + 1 == r) len[p] = 0;
    else len[p] = len[lp] + len[rp];
}

void update(int L, int R, int p, int l, int r, int io) {
    if (L <= l && r <= R) {
        tag[p] += io;
        up(p, l, r);
        return;
    }
    if (l + 1 == r) return; // 叶子节点
    if (L <= mid) update(L, R, ls, io);
    if (mid < R) update(L, R, rs, io);
    up(p, l, r);
}
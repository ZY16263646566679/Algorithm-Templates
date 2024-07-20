// 可持久化线段树（主席树）
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
// a[]: 原始数组，b[]: 离散化后的数组，rt: 主席树根节点，cnt: 主席树节点数量
int n, a[N], b[N], rt[N], cnt;
struct {
    // 左右子树，权值
    int l, r, v;
} t[N << 5];

// 离散化
int discretize() {
    sort(b + 1, b + 1 + n);
    return unique(b + 1, b + 1 + n) - (b + 1);
}

int build(int l, int r) {
    int p = ++cnt;
    t[p] = {l, r, 0};
    if (l == r) return p;
    int mid = (l + r) >> 1;
    t[p].l = build(l, mid);
    t[p].r = build(mid + 1, r);
    return p;
}

int update(int p, int v) {
    int q = ++cnt;
    t[q] = t[p], t[q].v++;
    if (t[q].l == t[p].l && t[q].r == t[p].r) return q;
    int mid = (t[q].l + t[q].r) >> 1;
    v <= mid ? t[q].l = update(t[q].l, v) : t[q].r = update(t[q].r, v);
    return q;
}

// 查询区间 [l, r] 中排名为 k 的元素，k in [1, r - l + 1]
int query(int l, int r, int k, int L = 1, int R = cnt) {
    if (L == R) return L;
    int mid = (L + R) >> 1;
    int x = t[t[r].l].v - t[t[l].l].v;
    if (k <= x)
        return query(t[l].l, t[r].l, k, L, mid);
    return query(t[l].r, t[r].r, k - x, mid + 1, R);
}
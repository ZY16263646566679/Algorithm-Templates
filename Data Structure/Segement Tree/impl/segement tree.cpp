#include <bits/stdc++.h>
using namespace std;

#define l(p) (p * 2)
#define r(p) (p * 2 + 1)

const int N = 1e5 + 5;
int n, v[N + 1];

// 下标要从1开始，因为0 * 2并不是0号节点的左儿子
struct node {
    int l, r, v, tag;
} t[N * 4];

void up(int p) {
    // t[p] = max(t[ls(p)], t[rs(p)]);
    t[p].v = t[l(p)].v + t[r(p)].v;
}

void build(int p, int l, int r) { // [l, r]
    t[p].l = l, t[p].r = r, t[p].tag = 0;
    if (l == r) {
        t[p].v = v[l];
        return;
    }
    int mid = l + r >> 1;
    build(l(p), l, mid);
    build(r(p), mid + 1, r);
    up(p);
}

void addtag(int p, int d) { // 如果只有单点修改，不需要用lazy-tag
    t[p].v += d * (t[p].r - t[p].l + 1); // 更新值
    t[p].tag += d; // 打标签
}

void down(int p) { // 标签往下传递，并更新子节点值
    if (!t[p].tag) return;
    addtag(l(p), t[p].tag);
    addtag(r(p), t[p].tag);
    t[p].tag = 0;
}

void update(int p, int L, int R, int d) { // [L, R]
    if (L <= t[p].l && t[p].r <= R) {
        addtag(p, d);
        return;
    }
    down(p);
    int mid = t[p].l + t[p].r >> 1;
    if (L <= mid) update(l(p), L, R, d);
    if (R > mid) update(r(p), L, R, d);
    up(p);
}

int query(int p, int L, int R) { // [L, R]
    if (L <= t[p].l && t[p].r <= R) return t[p].v;
    down(p);
    int mid = t[p].l + t[p].r >> 1;
    int res = 0;
    if (L <= mid) res += query(l(p), L, R);
    if (R > mid) res += query(r(p), L, R);
    return res;
}
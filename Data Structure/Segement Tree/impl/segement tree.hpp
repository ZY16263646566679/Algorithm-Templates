#include <bits/stdc++.h>
using namespace std;

#define mid (l + r >> 1)
#define l(p) (p << 1)
#define r(p) (p << 1 | 1)
#define ls l(p), l, mid
#define rs r(p), mid + 1, r

const int N = 1e5 + 5;
// 下标要从1开始，因为0 << 1并不是0号节点的左儿子
int n, v[N + 1], t[N << 2], tag[N << 2];

void up(int p) { t[p] = t[l(p)] + t[r(p)]; } // t[p] = max(t[ls(p)], t[rs(p)]);

void build(int p, int l, int r) { // 区间[l, r]
    tag[p] = 0;
    if (l == r) { t[p] = v[l]; return; }
    build(ls);
    build(rs);
    up(p);
}

void addtag(int p, int l, int r, int d) { // 如果只有单点修改，不需要用lazy-tag
    t[p] += d * (r - l + 1); // 更新值
    tag[p] += d; // 打标签
}

void down(int p, int l, int r) { // 标签往下传递，并更新子节点值
    addtag(ls, tag[p]);
    addtag(rs, tag[p]);
    tag[p] = 0;
}

void update(int L, int R, int p, int l, int r, int d) {
    if (L <= l && r <= R) { addtag(p, l, r, d); return; }
    if (tag[p]) down(p, l, r);
    if (L <= mid) update(L, R, ls, d);
    if (R > mid) update(L, R, rs, d);
    up(p);
}

int query(int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) return t[p];
    if (tag[p]) down(p, l, r);
    int res = 0;
    if (L <= mid) res += query(L, R, ls);
    if (R > mid) res += query(L, R, rs);
    // return max(query(L, mid, p << 1, l, mid), query(mid + 1, R, p << 1 | 1, mid + 1, R));
    return res;
}
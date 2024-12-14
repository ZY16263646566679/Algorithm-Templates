#include <bits/stdc++.h>
using namespace std;

struct segment_tree {
#define l(p) (p << 1)
#define r(p) (p << 1 | 1)

    struct node {
        int v;
        int l, r;
        int tag;
    };

    vector<int> v; // 下标从1开始
    vector<node> t;

    segment_tree(vector<int> v) {
        this->v = v;
        t.resize(v.size() << 2);
        build(1, 1, v.size() - 1);
    }

    void up(int p) {
        t[p].v = t[l(p)].v + t[r(p)].v;
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        t[p].tag = 0;
        if (l == r) {
            t[p].v = v[l];
            return;
        }
        build(l(p), l, (l + r) / 2);
        build(r(p), (l + r) / 2 + 1, r);
        up(p);
    }

    void addtag(int p, int d) {
        t[p].v += d * (t[p].r - t[p].l + 1);
        t[p].tag += d;
    }

    void down(int p) {
        addtag(l(p), t[p].tag);
        addtag(r(p), t[p].tag);
        t[p].tag = 0;
    }

    void update(int l, int r, int d, int p = 1) { // [l, r]
        if (l <= t[p].l && t[p].r <= r) {
            addtag(p, d);
            return;
        }
        if (t[p].tag) down(p);
        int mid = (t[p].l + t[p].r) / 2;
        if (l <= mid) update(l, r, d, l(p));
        if (r > mid) update(l, r, d, r(p));
        up(p);
    }

    int query(int l, int r, int p = 1) { // [l, r]
        if (l <= t[p].l && t[p].r <= r)
            return t[p].v;
        if (t[p].tag) down(p);
        int res = 0;
        int mid = (t[p].l + t[p].r) / 2;
        if (l <= mid) res += query(l, r, l(p));
        if (r > mid) res += query(l, r, r(p));
        return res;
    }
};
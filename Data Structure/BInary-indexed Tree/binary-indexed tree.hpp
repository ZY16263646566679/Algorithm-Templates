// 树状数组（也叫Fenwick Tree，因为是Peter M.Fenwick发明的）
#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) ((x) & -(x))
const int N = 1e5 + 5;
int n, tree[N]; // 下标从1开始，不然无法进行lowbit操作
void add(int x, int d) {
    while (x <= n) {
        tree[x] += d;
        x += lowbit(x);
    }
}
int sum(int x) { // [1, x]区间元素和
    int sum = 0;
    while (x) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

// 单点修改，区间查询[l, r]
void update(int x, int d) {
    add(x, d);
}
int query(int l, int r) {
    return sum(r) - sum(l - 1);
}

// 区间修改，单点查询（这时候的tree是差分数组构建出来的树）
void update(int l, int r, int d) {
    add(l, d);
    add(r + 1, -d);
}
int query(int x) {
    return sum(x);
}

/** 区间修改，区间查询[l, r]
 * sum(a[1...k]) = ∑ai = k * ∑di - ∑(i - 1) * di, (i in [1, k])
 * => 维护两个树状数组，一个是d[i]，另一个是(i - 1) * d[i]
 */
int tree1[N];
void add(bool flag, int x, int d) { // flag用于判断是维护哪个数组
    while (x <= n) {
        if (!flag) tree[x] += d;
        else tree1[x] += d;
        x += lowbit(x);
    }
}
int sum(bool flag, int x) {
    int sum = 0;
    while (x) {
        if (!flag) sum += tree[x];
        else sum += tree1[x];
        x -= lowbit(x);
    }
    return sum;
}
void update(int l, int r, int d) { // 区间修改
    add(0, l, d);
    add(0, r + 1, -d);
    add(1, l, d * (l - 1));
    add(1, r + 1, -d * r); // d * r = d * (r + 1 - 1)
}
int query(int l, int r) { // 区间查询
    int sum0 = (l - 1) * sum(0, l - 1) - sum(1, l - 1);
    int sum1 = r * sum(0, r) - sum(1, r);
    return sum1 - sum0;
}
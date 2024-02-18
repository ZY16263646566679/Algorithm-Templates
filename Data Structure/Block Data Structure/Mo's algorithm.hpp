// 莫队算法
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, a[N], pos[N], ans[N], cnt[N]; // n个元素，m个查询，元素下标均从1开始
struct node {
    int id, l, r;
    bool operator<(node& x) {
        if (pos[l] != pos[x.l])
            return pos[l] < pos[x.l];
        if (pos[l] & 1) return r > x.r; // 奇偶性优化
        return r < x.r;
    }
} q[N];
int ANS; // 区间内不同元素的数量
void add(int x) {
    cnt[a[x]]++;
    if (cnt[a[x]] == 1) ANS++;
}
void del(int x) {
    cnt[a[x]]--;
    if (cnt[a[x]] == 0) ANS--;
}
void Mo() {
    int block = sqrt(n);
    for (int i = 1; i <= n; i++) pos[i] = (i - 1) / block + 1;
    sort(q + 1, q + 1 + m);
    for (int i = 1, l = 1, r = 0; i <= m; i++) { // q[i]: [l, r]
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        ans[q[i].id] = ANS;
    }
}
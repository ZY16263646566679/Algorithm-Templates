// ST（Sparse Table，稀疏表）
#include <bits/stdc++.h>
using namespace std;
#define M(a, b) (a >= b ? a : b) // 最大值

const int maxn = 1e5 + 5;
int n, a[maxn], st[maxn][22]; // 下标从一开始
// 这里是求最大值
void init(int n) {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int i = 1, m = log2(n); i <= m; i++)
        for (int l = i, r = i + (1 << i - 1); l + (1 << i) <= n; l++, r++) // 左右两个子区间的左端点
            st[l][i] = M(st[l][i - 1], st[r][i - 1]);
}

// 查询区间[l, r]内的最值
int query(int l, int r) {
    int len = log2(r - l + 1);
    return M(st[l][len], st[r - (1 << len) + 1][len]);
}
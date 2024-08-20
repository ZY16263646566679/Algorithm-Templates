// ST（Sparse Table，稀疏表）
#include <bits/stdc++.h>
using namespace std;
#define M(a, b) (a >= b ? a : b) // 最大值

const int maxn = 1e5 + 5;
int n, a[maxn], st[maxn][22]; // 下标从1开始

// 这里是求最大值
void init(int n) {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int i = 1, m = __lg(n); i <= m; i++)
        for (int l = 1; l + (1 << i) <= n + 1; l++)
            st[l][i] = M(st[l][i - 1], st[l + (1 << i - 1)][i - 1]);
}

// 查询区间[l, r]内的最值
int query(int l, int r) {
    int len = __lg(r - l + 1);
    return M(st[l][len], st[r - (1 << len) + 1][len]);
}

// __lg函数是专门用来求以2为底的整数的对数的函数，内部使用__builtin_clz函数实现，返回值是int类型，效率比log2函数高
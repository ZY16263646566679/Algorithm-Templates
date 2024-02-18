// 分组背包
#include <bits/stdc++.h>
using namespace std;

/**
 * n 组物品，背包容量为 m
 * 每组物品只能选一个，第 i 组物品有 s[i] 个
 * 第 i 组第 j 个物品的体积和价值为 v[i][j] 和 w[i][j]
 */
const int N = 105, M = 1e4 + 5;
int n, m, s[N], v[N][N], w[N][N], f[M];

int solve() {
    for (int i = 1; i <= n; i++)
        for (int j = m; j; j--)
            for (int k = 1; k <= s[i]; k++) {
                if (j < v[i][k]) continue;
                f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
            }
    return f[m];
}

/**
 * n 个课程，m 天学习时间
 * 每门课只能选一次
 * w[i][j] 表示在 i 课程上花 j 天学习所获得的价值
 */
int n, m, f[105], w[105][105];

int solve() {
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 1; k <= m; k++) {
                if (k > j) break; // 剩余的背包容量 j 不够学习 k 天
                f[j] = max(f[j], f[j - k] + w[i][k]);
            }
    return f[m];
}
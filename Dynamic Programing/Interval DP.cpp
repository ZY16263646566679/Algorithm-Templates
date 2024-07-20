/**
 * 区间DP
 * dp[i][j]：合并区间[i, j]的最大/最小代价
 * dp[i][j] = min/max{ dp[i][k] + dp[k + 1][j] + w[i][j] }（k属于[i, j)，w[i][j]为合并区间[i, j]的代价）
 */

// 模板题——石子合并
#include <bits/stdc++.h>
using namespace std;

const int N = 305;
int n, a[N], s[N], dp[N][N]; // 下标从1开始

void init() {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;
}

void solve() {
    for (int len = 2; len <= n; len++) { // 区间长度
        for (int i = 1, j = i + len - 1; j <= n; i++, j++) { // i：左端点，j：右端点
            for (int k = i; k < j; k++) {
                int w = s[j] - s[i - 1];
                if (dp[i][k] + dp[k + 1][j] + w < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + w;
            }
        }
    }
}

/**
 * 如果石头堆是环形的，需要使用拆环成链的思想
 * 将右端点换成2 * n - 1，然后最后的答案为min/max{ dp[i][i + n - 1] }（i属于[1, n]）
 */
// 01背包问题
#include <bits/stdc++.h>
using namespace std;

// n：物品数量，V：背包体积，v[i]：物品体积，w[i]：物品价值
const int N = 1005;
int n, V, v[N], w[N];
int dp[N][N];

int solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < v[i]; j++)
            dp[i][j] = dp[i - 1][j];
        for (int j = v[i]; j <= V; j++)
            if (dp[i - 1][j - v[i]] + w[i] > dp[i][j])
                dp[i][j] = dp[i - 1][j - v[i]] + w[i];
            else dp[i][j] = dp[i - 1][j];
    }
}

vector<int> print() { // 打印路径
    vector<int> res;
    for (int i = n - 1, j = V; i >= 0; i--)
        if (dp[i][j] != dp[i - 1][j]) {
            res.push_back(w[i]);
            j -= w[i];
        }
    // 如果需要，逆序一下
    // reverse(res.begin(), res.end());
}

int solve() { // 滚动数组优化
    int dp[N] = {};
    for (int i = 0; i < n; i++)
        for (int j = V; j >= v[i]; j--) // 要从大到小
            if (dp[j] < dp[j - v[i]] + w[i])
                dp[j] = dp[j - v[i]] + w[i];
    return dp[V];
}
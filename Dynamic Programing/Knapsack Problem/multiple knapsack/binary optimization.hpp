// 多重背包の二进制优化
#include <bits/stdc++.h>
using namespace std;

// n：物品数量，V：背包体积，v[i]：物品体积，w[i]：物品价值
const int maxn = 1005, maxv = 2e4 + 5, maxcnt = 2e4 + 5;
int n, V, v[maxcnt], w[maxcnt], cnt; // cnt：组别的个数

void init() { // 转化成01背包 + 二进制优化
    cin >> n >> V;
    for (int i = 0, a, b, c; i < n; i++) {
        cin >> a >> b >> c;
        int k = 1; // 这一组的物品个数
        while (k <= c) {
            v[cnt] = a * k;
            w[cnt] = b * k;
            c -= k;
            k *= 2;
            cnt++;
        }
        if (c) { // 最后一组
            v[cnt] = a * c;
            w[cnt] = b * c;
            cnt++;
        }
    }
}

int dp[maxcnt][maxv]; // 此时的maxcnt、maxv不得超过1000
int solve() {
    for (int i = 0; i < cnt; i++) {
        for (int j = 1; j < v[i]; j++)
            dp[i][j] = dp[i - 1][j];
        for (int j = v[i]; j <= V; j++)
            if (dp[i][j - v[i]] + w[i] > dp[i][j])
                dp[i][j] = dp[i][j - v[i]] + w[i];
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
    int dp[maxv] = {};
    for (int i = 0; i < cnt; i++)
        for (int j = V; j >= v[i]; j--)
            if (dp[j] < dp[j - v[i]] + w[i])
                dp[j] = dp[j - v[i]] + w[i];
    return dp[V];
}
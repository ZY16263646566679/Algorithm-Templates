/** 多重背包の单调队列优化
 * dp[j]    =     dp[j]
 * dp[j+v]  = max(dp[j] +  w,  dp[j+v])
 * dp[j+2v] = max(dp[j] + 2w,  dp[j+v] +  w, dp[j+2v])
 * dp[j+3v] = max(dp[j] + 3w,  dp[j+v] + 2w, dp[j+2v] + w, dp[j+3v])
 * ...
 * 但是，这个队列中前面的数，每次都会增加一个 w ，所以我们需要做一些转换
 * dp[j]    =     dp[j]
 * dp[j+v]  = max(dp[j], dp[j+v] - w) + w
 * dp[j+2v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w) + 2w
 * dp[j+3v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w, dp[j+3v] - 3w) + 3w
 * ...
 * 这样，每次入队的值是 dp[j+k*v] - k*w
 */

#include <bits/stdc++.h>
using namespace std;

// n：物品数量，V：背包体积
const int maxv = 2e4 + 5;
int n, V, dp[maxv];
deque<vector<int>> q; // 单调队列优化

int solve() {
    cin >> n >> V;
    for (int i = 0, v, w, c; i < n; i++) { // v：物品体积，w：物品价值，c：物品数量
        cin >> v >> w >> c;
        for (int j = 0; j < v; j++) { // 根据V对v求余的值分组，因为dp[k]是从k求余v相同的dp[k - v]，dp[k - 2 * v]，dp[k - 3 * v]，...转移来的
            for (int k = j; k <= V; k += v) {
                while (q.size() && q.back()[0] <= dp[k] - k / v * w) q.pop_back(); // 队头->队尾：大->小
                q.push_back({ dp[k] - k / v * w, k / v });
                while (k / v - q.front()[1] > c) q.pop_front(); // 窗口大小为c
                dp[k] = q.front()[0] + k / v * w;
            }
            q.clear();
        }
    }
    return dp[V];
}
/**
 * 多重背包の单调队列优化
 * dp[i]    =     dp[i]
 * dp[i+v]  = max(dp[i] +  w,  dp[i+v])
 * dp[i+2v] = max(dp[i] + 2w,  dp[i+v] +  w, dp[i+2v])
 * dp[i+3v] = max(dp[i] + 3w,  dp[i+v] + 2w, dp[i+2v] + w, dp[i+3v])
 * ...
 * 但是，这个队列中前面的数，每次都会增加一个 w ，所以我们需要做一些转换
 * dp[i]    =     dp[i]
 * dp[i+v]  = max(dp[i], dp[i+v] - w) + w
 * dp[i+2v] = max(dp[i], dp[i+v] - w, dp[i+2v] - 2w) + 2w
 * dp[i+3v] = max(dp[i], dp[i+v] - w, dp[i+2v] - 2w, dp[i+3v] - 3w) + 3w
 * ...
 * 这样，每次入队的值是 dp[i+k*v] - k*w
 */

#include <bits/stdc++.h>
using namespace std;

// n：物品数量，V：背包体积
const int maxv = 2e4 + 5;
int n, V, dp[maxv];
deque<pair<int, int>> q;

int solve() {
    cin >> n >> V;
    for (int v, w, c; n--;) { // v：物品体积，w：物品价值，c：物品数量
        cin >> v >> w >> c;
        for (int i = 0; i < v; i++) { // 根据V对v求余的值分组，因为dp[k]是从与k求余v相同的dp[k - v]，dp[k - 2 * v]，dp[k - 3 * v]，...转移来的
            for (int k = i; k <= V; k += v) {
                while (q.size() && q.back().first <= dp[k] - k / v * w) q.pop_back(); // 队头->队尾：大->小
                q.push_back({ dp[k] - k / v * w, k / v });
                while (k / v - q.front().second > c) q.pop_front(); // 窗口大小为c
                dp[k] = q.front().first + k / v * w;
            }
            q.clear();
        }
    }
    return dp[V];
}
// 最长路径问题
#include <bits/stdc++.h>
using namespace std;

/**
 * 对于 DAG（Directed Acyclic Graph，有向无环图）
 * 算法：拓扑排序 + DP
 * 例题：https://www.luogu.com.cn/problem/P1807
 */
const int N = 1505, inf = 0x3f3f3f3f;
int n, m, deg[N], dis[N];
vector<pair<int, int>> e[N];
queue<int> q;

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        dis[i] = -inf;
    for (int i = m, u, v, w; i--;) {
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        deg[v]++;
    }
    q.push(1), dis[1] = 0;
    for (int i = 2; i <= n; i++)
        if (!deg[i]) q.push(i);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (auto& [v, w] : e[u]) {
            dis[v] = max(dis[v], dis[u] + w);
            if (!--deg[v]) q.push(v);
        }
    }
    cout << (dis[n] + inf ? dis[n] : -1);
}

/**
 * 关于 DAG
 * DAG 是一种性质很好的图，因为它很容易进行 DP。在 DAG 上搜索的效率也会比更搞。
 * 比它性质更好的图是树。
 */

/**
 * 对于一般的图
 * 算法：SPFA
 * 将更新过最长距离的节点放入队列等待再次更新。
 */
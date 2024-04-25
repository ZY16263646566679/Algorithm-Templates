#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using vpii = vector<pii>;

const int N = 1e5 + 5, inf = 0x7fffffff;
vpii e[N];
int n, m, dis[N], pre[N];

void init() { // 初始化
    for (int i = 0; i < n; i++) { // 节点从0开始编号
        dis[i] = inf;
        pre[i] = 0;
    }
}

// 堆优化的 Dijkstra，平均时间复杂度O(mlogn)，最坏时间复杂度（稠密图）O(n²logn)
void dijkstra(int s) {
    init();
    priority_queue<pii, vpii, greater<pii>> q; // first 为起点到 second 的距离
    q.push({ 0, s });
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (dis[u] < d) continue;
        dis[u] = d;
        for (auto& [v, w] : e[u])
            if (d + w < dis[v]) {
                dis[v] = d + w; // 小优化
                q.push({ d + w, v });
                pre[v] = u;
            }
    }
}

// 朴素的 Dijkstra，时间复杂度O(n²)
void dijkstra(int s) { // 以 s 为起点
    init();
    bool done[N];
    memset(done, 0, sizeof(done));
    dis[s] = 0;
    for (int i = 0; i < n - 1; i++) { // 只需 n - 1 次即可
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!done[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        done[u] = true;
        for (auto& [v, w]: e[u])
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = u;
            }
    }
}
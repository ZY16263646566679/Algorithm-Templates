#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using vpii = vector<pii>;

const int N = 1e5 + 5;
vpii e[N];
int n, m, dis[N], pre[N];
bool done[N];

void init() { // 初始化
    for (int i = 0; i < n; i++) { // 节点从0开始编号
        dis[i] = 0x3f3f3f3f;
        pre[i] = 0;
        done[i] = 0;
    }
}

// 朴素的 Dijkstra，时间复杂度O(n²)
void dijkstra(int s) { // 以 s 为起点
    init();
    dis[s] = 0;
    for (int i = 0; i < n - 1; i++) { // 只需 n - 1 次即可
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!done[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        done[u] = true;
        for (auto [v, w]: e[u])
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = u;
            }
    }
}

// 堆优化的 Dijkstra，平均时间复杂度O(mlogn)，最坏时间复杂度（稠密图）O(n²logn)
void dijkstra(int s) {
    init();
    dis[s] = 0;
    priority_queue<pii, vpii, greater<pii>> q; // first为点second到起点的距离
    q.push({ 0, s });
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (done[u]) continue;
        done[u] = true;
        for (auto& [v, w] : e[u])
            if (d + w < dis[v]) {
                dis[v] = d + w;
                q.push({ dis[v], v });
                pre[v] = u;
            }
    }
}
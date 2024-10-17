// Prim 算法求最小生成树
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>; // first：距离，second：节点编号

const int N = 5005;

vector<pii> e[N];
int n, m, dis[N];
bool done[N];

// 堆优化版 Prim，时间复杂度 O(mlogn)，适合稀疏图
int prim() {
    int ans = 0, cnt = 0;
    priority_queue<pii, vector<pii>, greater<>> q;
    q.push({ 0, 1 });
    memset(dis, 0x7f, sizeof(dis));
    while (!q.empty()) {
        auto [w, u] = q.top(); q.pop();
        if (done[u]) continue;
        ans += w;
        if (++cnt == n) break;
        done[u] = true;
        for (auto& [v, w] : e[u]) {
            if (done[v] || w >= dis[v]) continue; // 小优化
            dis[v] = w, q.push({ w, v });
        }
    }
    return cnt == n ? ans : -1; // 如果cnt != n，说明图不是连通的
}

// 朴素版 Prim，时间复杂度 O(n^2)，适合稠密图
int prim_naive() {
    int ans = 0, cnt = 0;
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1, mn = 0x7f7f7f7f;
        for (int j = 1; j <= n; j++)
            if (!done[j] && dis[j] < mn)
                u = j, mn = dis[j];
        if (u == -1) return -1;
        ans += mn, done[u] = true;
        if (++cnt == n) break;
        for (auto& [v, w] : e[u])
            if (!done[v] && w < dis[v])
                dis[v] = w;
    }
    return ans;
}

/**
 * 堆优化版是“边优先”的，而朴素版是“点优先”的
 * 稀疏图的情况类似于 n <= 1e5，m <= 5e5；
 * 稠密图的情况类似于 n <= 5e3，m <= 2e7；
 * 这和 Dijkstra 算法类似。
 */
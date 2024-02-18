#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using vpii = vector<pii>;

const int N = 1e5 + 5;
vpii e[N];
int n, m, s, dis[N], pre[N];
bool done[N];
void init() { // 初始化
    for (int i = 0; i < n; i++) { // 节点从0开始编号
        dis[i] = 0x3f3f3f3f;
        pre[i] = 0;
        done[i] = 0;
    }
}
void dijkstra(int s) {
    init();
    dis[s] = 0;
    std::priority_queue<pii, vpii, greater<pii>> q; // first为点second到起点的距离
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

struct point { // 评估函数：f = g + h（g为到起点s的距离，h为到终点t的距离）
    int id, g, h;
    bool operator<(const point& p) const { return g + h > p.g + p.h; }
};
int times[N];
int astar(int s, int t, int k) { // A*算法求第k短路径
    memset(times, 0, n << 2);
    std::priority_queue<point> q;
    q.push({ s, 0, 0 });
    while (!q.empty()) {
        point p = q.top();
        q.pop();
        times[p.id]++;
        if (p.id == t && times[p.id] == k)
            return p.g + p.h;
        for (int i = 0, n = e[p.id].size(); i < n; i++) {
            auto [v, w] = e[p.id][i];
            q.push({ v, p.g + w, dis[v] }); // dis[i]为i到终点的最短距离
        }
    }
    return -1;
}
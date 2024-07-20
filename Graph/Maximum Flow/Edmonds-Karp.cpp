// BFS每次计算一次“最短”的增广路径
#include <bits/stdc++.h>
using namespace std;

const int N = 255, INF = INT_MAX;
int n, m, G[N][N], pre[N], flow[N];

int bfs(int s, int t) {
    memset(pre, -1, sizeof(pre));
    flow[s] = INF, pre[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u =  q.front(); q.pop();
        if (u == t) break;
        for (int i = 1; i <= n; i++) {
            if (i - s && G[u][i] && pre[i] == -1) { // i不是起点，u -> i存在路径，没到达过i
                pre[i] = u;
                q.push(i);
                flow[i] = min(flow[u], G[u][i]);
            }
        }
    }
    if (pre[t] == -1) return -1; // 没有找到增广路径
    return flow[t];
}

int maxflow(int s, int t) {
    int Maxflow = 0;
    while (true) {
        int flow = bfs(s, t);
        if (flow == -1) break;
        int cur = t;
        while (cur - s) {
            int fa = pre[cur];
            G[fa][cur] -= flow; // 正向相减
            G[cur][fa] += flow; // 反向相加
            cur = fa;
        }
        Maxflow += flow;
    }
    return Maxflow;
}
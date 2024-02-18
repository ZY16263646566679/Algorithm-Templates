// Tarjan--离线算法，时间复杂度O(m + n)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, s[N], ans[N]; // 下标从1开始，ans[id]：编号为id的查询的答案
bool vis[N]; // vis[u]为真代表u的祖先节点已经遍历完毕
vector<int> e[N];
vector<pair<int, int>> q[N]; // q[u]: { {v1, id1}, {v2, id2}... }

void init() {
    iota(s + 1, s + 1 + n, 1);
    memset(vis + 1, 0, n);
}

int find(int x) {
    return x == s[x] ? x : s[x] = find(s[x]);
}

void tarjan(int u) { // 从根节点u开始
    vis[u] = true;
    for (int v : e[u]) {
        if (vis[v]) continue;
        tarjan(v);
        s[v] = u;
    }
    for (auto& [v, id] : q[u])
        if (vis[v])
            ans[id] = find(v);
}
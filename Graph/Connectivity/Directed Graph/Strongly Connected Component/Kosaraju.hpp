#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> g[N], rg[N], s; // 节点下标从1开始
int n, sccno[N], cnt;
bool vis[N];

void dfs1(int u) {
    if (vis[u]) return;
    vis[u] = true;;
    for (int v : g[u]) dfs1(v);
    s.push_back(u);
}

void dfs2(int u) {
    if (sccno[u]) return;
    sccno[u] = cnt;
    for (int v : rg[u]) dfs2(v);
}

void kosaraju() {
    for (int i = 1; i <= n; i++) dfs1(i);
    for (int i = n - 1; i >= 0; i--)
        if (!sccno[s[i]]) dfs2(s[i]);
}
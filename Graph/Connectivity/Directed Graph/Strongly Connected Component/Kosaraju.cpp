// Kosaraju 算法求强连通分量
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
/**
 * 节点下标从1开始
 * s[]：点的先后顺序，递归越深的点位置越靠前
 * 逆序遍历反图过程中，强连通分量会被“堵住”
 */
vector<int> g[N], rg[N], s;
int n, sccno[N], cnt;
bool vis[N];

void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v]) dfs1(v);
    s.push_back(u);
}

void dfs2(int u) {
    sccno[u] = cnt;
    for (int v : rg[u])
        if (!sccno[v]) dfs2(v);
}

void kosaraju() {
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs1(i);
    for (int i = n - 1; i >= 0; i--)
        if (!sccno[s[i]])
            cnt++, dfs2(s[i]);
}
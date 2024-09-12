// 树链剖分（默认为重链剖分）求LCA
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, d[N], sz[N], hson[N], top[N], fa[N]; // top[u]：表示节点u所在重链的顶部节点
vector<int> e[N];

void dfs1(int u, int f) {
    d[u] = d[f] + 1;
    sz[u] = 1;
    for (int v : e[u]) {
        if (v == f) continue;
        fa[v] = u;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[hson[u]]) hson[u] = v;
    }
}

void dfs2(int u, int t) { // 节点u所在重链的顶部节点为t
    top[u] = t;
    if (hson[u]) dfs2(hson[u], t);
    for (int v : e[u])
        if (v != fa[u] && v != hson[u])
            dfs2(v, v);
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (d[top[u]] > d[top[v]]) swap(u, v); // make sure d[u] <= d[v]
        v = fa[top[v]];
    }
    return d[u] < d[v] ? u : v;
}
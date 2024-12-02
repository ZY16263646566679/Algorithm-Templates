// Tarjan 算法求强连通分量
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, low[N], num[N], dfn, cnt; // 节点下标从1开始
int sccno[N], st[N], top;
vector<int> e[N];

void dfs(int u) {
    st[top++] = u;
    low[u] = num[u] = ++dfn;
    for (int v : e[u]) {
        if (!num[v]) dfs(v);
        if (!sccno[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] != num[u]) return;
    cnt++; // SCC 数量加一
    while (1) {
        int v = st[--top];
        sccno[v] = cnt;
        if (u == v) break;
    }
}

void tarjan() {
    for (int i = 1; i <= n; i++)
        if (!num[i]) dfs(i);
}

/**
 * 还有另外一种写法
 * if (!num[v]) {
 *     dfs(v);
 *     low[u] = min(low[u], low[v]);
 * } else if (!sccno[v]) low[u] = min(low[u], num[v]);
 * 注意，同一个强连通分量中的节点的low值并不一定相同，但是同一个强连通分量中一定只有一个节点的low值等于自己的num值（dfs序）
 */

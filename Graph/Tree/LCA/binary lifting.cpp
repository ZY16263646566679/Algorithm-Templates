// 倍增法--在线算法，时间复杂度O((n + m)logn)
#include <bits/stdc++.h>
using namespace std;

/**
 * 节点编号和数组下标从1开始
 * anc[x][i]：节点x的第2的i次方个祖先节点
 * d[x]：节点x的深度（根节点的深度是1）
 * dis[x]：节点x距离根节点的距离（有权树）
 */
const int N = 1e5 + 5;
int n, anc[N][20], d[N], dis[N];
vector<pair<int, int>> e[N];

void dfs(int u, int fa) { // 调用：dfs(root, 0)
    d[u] = d[fa] + 1;
    anc[u][0] = fa;
    for (int i = 1; (1 << i) < d[u]; i++) // 根节点是节点x的第d[x] - 1个祖先节点
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (auto& [v, w] : e[u])
        if (v != fa) { // 除了父节点，都是孩子
            dis[v] = dis[u] + w;
            dfs(v, u);
        }
}

int lca(int x, int y) {
    if (d[x] < d[y]) swap(x, y); // 令x比y深
    for (int i = 19; i >= 0; i--)
        if (d[x] - (1 << i) >= d[y])
            x = anc[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--) // 祖先相等说明跳过头了，换一个小的i重复跳
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0]; // 最后x位于LCA的下一层，父节点就是LCA
}

int distance(int x, int y) {
    return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}
// LCA的应用：树上差分
#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
int n, fa[N][20], d[N], D[N]; // d[x]：节点x的深度，D[x]：节点x到根的距离
vector<int> e[N];

void dfs(int u, int father) {
    d[u] = d[father] + 1;
    fa[u][0] = father;
    for (int i = 1; (1 << i) < d[u]; i++) // 根节点是节点x的第d[x] - 1个祖先节点
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v : e[u])
        if (v != father) // 除了父节点，都是孩子
            D[v] += D[u], dfs(v, u); // 更新到根的距离
}

int lca(int x, int y) {} // 倍增法求LCA，此处代码略去

void diff(int u, int v, int x) { // u -> v路径上每个节点权值加x
    int a = lca(u, v);
    D[u] += x, D[v] += x, D[a] -= x, D[fa[a][0]] -= x;
}

void dfs(int u, int father, int t) { // 差分：dfs(1, 0, 0)，恢复：dfs(1, 0, 1)
    for (int v : e[u]) {
        if (v == father) continue;
        dfs(v, u);
        if (t) D[u] -= D[v]; // 差分
        else D[u] += D[v]; // 恢复
    }
}
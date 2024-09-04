// LCA 最优解：DFS 序
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
// 下标从1开始，dfn[]：时间戳
int n, m, rt, dfn[N], st[N][19], cnt;
vector<int> e[N];

#define M(x, y) (dfn[x] < dfn[y] ? x : y)

void dfs(int u, int fa) {
    st[dfn[u] = ++cnt][0] = fa; // 存储父节点
    for (int v : e[u])
        if (v != fa)
            dfs(v, u);
}

void initST() {
    for (int i = 1; i <= __lg(n); i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            // 父节点中时间戳最小的
            st[j][i] = M(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
}

int lca(int u, int v) {
    if (u == v)
        return u;
    if ((u = dfn[u]) > (v = dfn[v]))
        swap(u, v);
    int d = __lg(v - u++); // 适用 u 是 v 的祖先节点的情况（关键）
    return M(st[u][d], st[v - (1 << d) + 1][d]);
}

// from：https://www.luogu.com.cn/article/pu52m9ue
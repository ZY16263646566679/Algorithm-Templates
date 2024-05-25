// Tarjan 算法求割边（桥）
#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 5;
int low[N], num[N], dfn; // root is node 1, num[u]: dfn of u
bool iscut[N];
vector<int> e[N]; // 邻接表存图

/**
 * 求割边
 * 注意：在求割边的问题中，两个点不能构成一个“环”，中间是有割边的。
 * 没有割边的连通分量称之为边双连通分量
 */
vector<pair<int, int>> bridge;

void dfs(int u, int fa) {
    low[u] = num[u] = ++dfn;
    for (int v : e[u]) {
        if (v == fa) continue;
        if (num[v]) { // 处理回退边
            low[u] = min(low[u], num[v]);
            continue;
        }
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] > num[u]) // u ←→ v 是割边
            bridge.push_back({u, v});
    }
    // 也可以这样写：
    // if (low[u] == num[u] && fa != 0) // fa ←→ u 是割边
    //     bridge.push_back({fa, u});
}

// 特殊地，只有一个点的图既没有割点，也没有桥
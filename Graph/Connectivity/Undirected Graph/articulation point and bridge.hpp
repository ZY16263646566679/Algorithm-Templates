// Tarjan 算法求割点/割边（桥）
#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 5;
int low[N], num[N], dfn; // root is node 1, num[u]: dfn of u
bool iscut[N];
vector<int> e[N]; // 邻接表存图

// 求割点
void dfs(int u) {
    low[u] = num[u] = ++dfn;
    int child = 0;
    for (int v : e[u]) { // u ←→ v
        if (num[v]) { // v 被访问过
            low[u] = min(low[u], num[v]);
            continue;
        }
        child++;
        dfs(v);
        low[u] = min(low[u], low[v]); // 用后代的 low 值更新 low 值
        if (low[v] >= num[u] && u - 1)
            iscut[u] = true;
    }
    if (u == 1 && child >= 2)
        iscut[1] = true;
}

// 求割边
vector<pair<int, int>> bridge;

void dfs(int u, int fa) {
    low[u] = num[u] = ++dfn;
    for (int v : e[u]) {
        if (v == fa) continue;
        if (num[v]) {
            low[u] = min(low[u], num[v]);
            continue;
        }
        dfs(v);
        low[u] = min(low[u], low[v]);
        if (low[v] > num[u]) // u ←→ v 是割边
            bridge.push_back({u, v});
    }
    // 也可以这样写：
    // if (low[u] == num[u] && fa != 0) // fa ←→ u 是割边
    //     bridge.push_back({fa, u});
}
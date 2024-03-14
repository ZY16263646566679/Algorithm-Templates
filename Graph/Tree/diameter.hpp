// 树的直径——两次DFS
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, dis[N]; // dis[i]：i到起点的距离
vector<pair<int, int>> e[N]; // 到first的距离为second

void dfs(int u, int fa) {
    for (auto& [v, w] : e[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u);
    }
}

int diameter() {
    int st = 1, ed = 1;
    dfs(1, 0); // 先求起点
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[st]) st = i;
    dis[st] = 0;
    dfs(st, 0); // 再求终点
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[ed]) ed = i;
    return dis[ed];
}

/**
 * 法二：树形DP
 * d1，d2：到叶子节点的最长和次长路
 * root：直径在树中的根节点
 * pre1，pre2：最长和次长路的前驱节点
 */
int d1[N], d2[N], root, pre1[N], pre2[N]; 

void dfs(int u, int fa) {
    d1[u] = d2[u] = 0;
    for (auto& [v, w] : e[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u);
        int t = d1[v] + w;
        if (t > d1[u]) {
            d2[u] = d1[u], d1[u] = t;
            pre2[u] = pre1[u], pre1[u] = v;
        } else if (t > d2[u]) {
            d2[u] = t;
            pre2[u] = v;
        }
    }
    if (d1[u] + d2[u] > d1[root] + d2[root]) root = u;
}

vector<int> get_path() {
    int st = root, ed = root;
    deque<int> path { root };
    while (pre1[st]) path.push_front(st = pre1[st]);
    while (pre2[ed]) path.push_back(ed = pre2[ed]);
    return vector<int>(path.begin(), path.end());
}
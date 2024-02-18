// 求割点/割边（桥）
#include <bits/stdc++.h>
using namespace std;

const int N = 109;
int low[N], num[N], dfn; // root is node 1, num[u]: dfn of u
bool iscut[N];
vector<int> e[N]; // 邻接表存图

void dfs(int u, int fa) {
    low[u] = num[u] = ++dfn;
    int child = 0;
    for (int v : e[u]) { // u -> v
        if (num[v]) continue; // v被访问过
        child++;
        dfs(v, u);
        if(low[v] < low[u]) low[u] = low[v]; // 用后代的low值更新low值
        if (low[v] >= num[u] && u - 1) // 换成 > 就是求割边
            iscut[u] = true;
    }
    if (u == 1 && child >= 2)
        iscut[1] = true;
}

// 在求割边时，如果iscnt[u]为真，(father[u], u)为一条割边
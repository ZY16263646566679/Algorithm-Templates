// 树上启发式合（时间复杂度O(nlogn)）
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 模板
const int N = 1e5 + 5;
int n, dep[N], sz[N], hson[N]; // 节点下标从1开始，hson[i]为0表示节点i没有重儿子
vector<int> edges[N];

void dfs0(int u, int fa = -1) {
    int mx = 0, size = 1;
    for (int v : edges[u])
        if (v != fa) {
            dfs0(v, u);
            size += sz[v];
            if (sz[v] > mx) hson[u] = v, mx = sz[v];
        }
    sz[u] = size;
}

void add(int u) { // add operation

}

void del(int u) { // del operation

}

void addsubtree(int u, int fa = -1) { // 增加一个子树的统计信息
    add(u);
    for (int v : edges[u])
        if (v != fa)
            addsubtree(v, u);
}

void delsubtree(int u, int fa = -1) { // 删除一个子树的统计信息
    del(u);
    for (int v : edges[u])
        if (v != fa)
            delsubtree(v, u);
}

void dfs(int u, int fa = -1, bool keep = true) {
    for (int v : edges[u])
        if (v != fa && v != hson[u])
            dfs(v, u, false);
    if (hson[u]) dfs(hson[u], u, true); // 保留重儿子信息
    add(u);
    for (int v : edges[u])
        if (v != fa && v != hson[u]) // 累加轻儿子信息
            addsubtree(v, u);
    /* 计算合并结果 begin */
    
    /* end */
    if (!keep) { // 不保留该子树的信息
        delsubtree(u, fa);
        // 其它清零操作
    }
}

// 模板题https://codeforces.com/problemset/problem/600/E
int color[N], cnt[N], maxn; // 节点下标从1开始
ll sum, ans[N]; // ans[i]：节点i的启发式合并结果

void add(int u) { // 增加一个节点的统计信息
    int n = ++cnt[color[u]];
    if (n > maxn) {
        maxn = n, sum = color[u];
    } else if (n == maxn) {
        sum += color[u];
    }
}

void del(int u) { // 删除一个节点的统计信息
    --cnt[color[u]];
}

// 还可以利用子树的dfs序（DFS Numbering）连续的性质，直接循环而不是递归进行addsubtree和delsubtree
// 修改后的两个dfs函数；不再需要单独写出addsubtree和delsubtree函数
int sz[N], hson[N], L[N], R[N], node[N], cdfsn;

void dfs0(int u, int fa = -1) {
    L[u] = ++cdfsn;
    node[cdfsn] = u;
    int ma = 0, size = 1;
    for (int v : edges[u])
        if (v != fa) {
            dfs0(v, u);
            size += sz[v];
            if (sz[v] > ma) hson[u] = v, ma = sz[v];
        }
    sz[u] = size;
    R[u] = cdfsn;
}

void dfs(int u, int fa = -1, bool keep = 1) {
    for (int v : edges[u])
        if (v != fa && v != hson[u])
            dfs(v, u, 0);
    if (hson[u]) dfs(hson[u], u, 1);
    add(u);
    for (int v : edges[u])
        if (v != fa && v != hson[u])
            for (int i = L[v]; i <= R[v]; ++i)
                add(node[i]);
    ans[u] = sum;
    if (!keep) {
        for (int i = L[u]; i <= R[u]; ++i)
            del(node[i]);
        maxn = sum = 0;
    }
}

/**
 * 更好理解的启发式合并：将小树合并到大树，时间复杂度也是O(nlogn)
 * if (t1.size() < t2.size()) swap(t1, t2);
 * t1.merge(t2);
 */
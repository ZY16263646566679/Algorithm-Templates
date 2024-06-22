// Kruskal 算法求最小生成树
#include <bits/stdc++.h>
using namespace std;

// 时间复杂度 O(mlogm)，实际运行效率高于 Prim
const int N = 5005;
struct edge {
    int u, v, w;
    bool operator<(const edge& rhs) const {
        return w < rhs.w;
    }
} e[N * N / 2];

int n, m, s[N]; // 下标从1开始

int find(int x) {
    return x == s[x] ? x : s[x] = find(s[x]);
}

int kruskal() {
    sort(e, e + m);
    for (int i = 1; i <= n; i++) s[i] = i;
    int ans = 0, cnt = 1;
    for (int i = 0; i < m; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        ans += e[i].w;
        s[u] = v; // 合并
        if (++cnt == n) break;
    }
    return cnt == n ? ans : -1; // 如果cnt != n，说明图不是连通的
}
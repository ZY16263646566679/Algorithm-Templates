#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
struct edge {
    int u, v, w;
    bool operator<(const edge &rhs) const {
        return w < rhs.w;
    }
} e[N << 1];
int n, m, s[N];

int find(int x) {
    return x == s[x] ? x : s[x] = find(s[x]);
}

int kruskal() {
    sort(e, e + m);
    for (int i = 1; i <= n; i++) s[i] = i;
    int ans = 0, cnt = 1;
    for (int i = 1; i <= m; i++) {
        if (cnt == n) break;
        int e1 = find(e[i].u), e2 = find(e[i].v);
        if (e1 == e2) continue;
        ans += e[i].w;
        s[e1] = e2; // 合并
        cnt++;
    }
    return cnt == n ? ans : -1; // 如果cnt != n，说明图不是连通的
}
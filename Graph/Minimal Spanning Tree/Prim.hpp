// Prim 算法求最小生成树
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>; // first：距离，second：节点编号

const int N = 5005;

vector<pii> e[N];
int n, m;
bool done[N];

int prim() {
    int ans = 0, cnt = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({ 0, 1 });
    while (!q.empty()) {
        auto [w, u] = q.top(); q.pop();
        if (done[u]) continue;
        ans += w;
        if (++cnt == n) break;
        done[u] = true;
        for (auto& [v, w] : e[u]) {
            if (done[v]) continue;
            q.push({ w, v });
        }
    }
    return cnt == n ? ans : -1; // 如果cnt != n，说明图不是连通的
}
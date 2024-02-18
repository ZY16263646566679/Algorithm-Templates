#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>; // first：距离，second：节点编号

const int N = 5005;
struct edge {
    int u, v, w;
};

vector<edge> e[N];
int n, m;
bool done[N];

int prim() {
    int ans = 0, cnt = 1;
    std::priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({ 0, 1 });
    while (!q.empty()) {
        pii p = q.top();
        q.pop();
        ans += p.first;
        if (done[p.second]) continue;
        done[p.second] = true;
        for (int i = 0, n = e[p.second].size(); i < n; i++) {
            edge x = e[p.second][i];
            if (done[x.v]) continue;
            q.push({ x.w, x.v });
        }
    }
    return cnt == n ? ans : -1; // 如果cnt != n，说明图不是连通的
}
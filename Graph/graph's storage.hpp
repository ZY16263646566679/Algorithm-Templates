#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
using vpii = vector<pii>;

const int N = 1e5;

namespace AdjacencyList {
    int n;
    vi e1[N];

    void addedge(int u, int v) {
        e1[u].push_back(v);
        e1[v].push_back(u);
    }

    vpii e2[N];

    void addedge(int u, int v, int w) {
        e2[u].push_back({ v, w });
        e2[v].push_back({ u, w });
    }
}

namespace ForwardStar {
    int n, head[N], cnt;
    
    struct edge {
        int to, w, next;
    } e[N];

    void init() {
        for (int i = 0; i < n; i++) head[i] = -1;
    }

    void addedge(int u, int v, int w) {
        e[cnt].to = v;
        e[cnt].w = w;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }

    void traverse(int u) {
        for (int i = head[u]; ~i; i = e[i].next) {
            // 操作
        }
    }
}
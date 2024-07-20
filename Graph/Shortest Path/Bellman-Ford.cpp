// 单源最短路径算法，O(mn)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5, INF = INT_MAX;
// 使用最简单的结构体数组存边
struct Edge {
    int u, v, w;
} e[N];

int n, dis[N], cnt;

void init(int s) {
    for (int i = 0; i < n; i++) dis[i] = INF;
    dis[s] = 0;
}

void bellman_ford(int s) {
    init(s);
    for (int i = n; i--;)
        for (int j = 0; j < cnt; j++) {
            int from = e[j].u, to = e[j].v, w = e[j].w;
            if (dis[from] + w < dis[to]) dis[to] = dis[from] + w;
        }
}
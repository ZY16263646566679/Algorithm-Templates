// Floyd算法--DP，并打印路径
// 时间复杂度O(n^3)，无法判断负环
#include <bits/stdc++.h>
using namespace std;

// 节点从1开始编号
const int N = 305, INF = INT_MAX; // N：该时间复杂度下最大允许的图的大小
int n, m, G[N][N], path[N][N]; // n：节点数，m：边数，path[i][j]：i到j的最短路径的下一个节点

void init() { // 下标从1开始
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i - j) {
                G[j][i] = G[i][j] = INF; // 初始化为无穷大
                path[i][j] = j;
                path[j][i] = i;
            }
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        G[v][u] = G[u][v] = w; // 无向图
        // G[u][v] = w; // 有向图
        // 如果有两个相邻节点之间可能会有多条边，还需要再取最小值
    }
}
void floyd() { // 有向图
    for (int k = 1; k <= n; k++) // k循环必须写在外层
        for (int i = 1; i <= n; i++) {
            if (G[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (G[k][j] == INF) continue;
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[i][j] = G[i][k] + G[k][j]; // G[i][i] < 0：存在负环
                    path[i][j] = path[i][k];
                } else if (G[i][k] + G[k][j] == G[i][j] && path[i][j] > path[i][k]) // 若距离相同，要字典序最小的路径
                    path[i][j] = path[i][k];
            }
        }

}

void floyd() { // 无向图
    for (int k = 1; k <= n; k++)
        for (int i = 1; i < n; i++) {
            if (G[i][k] == INF) continue;
            for (int j = i + 1; j <= n; j++) {
                if (G[k][j] == INF) continue;
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[j][i] = G[i][j] = G[i][k] + G[k][j]; // 对称性
                    path[i][j] = path[i][k];
                    path[j][i] = path[j][k];
                } else if (G[i][k] + G[k][j] == G[i][j]) {
                    if (path[i][j] > path[i][k]) path[i][j] = path[i][k];
                    if (path[j][i] > path[j][k]) path[j][i] = path[j][k];
                }
            }
        }
}


void print_path(int x, int y) {
    while (path[x][y]) { // 为零说明到达了
        cout << path[x][y] << ' ';
        x = path[x][y];
    }
}

// 传递闭包
const int N = 1005;
int n, m;
bitset<N> d[N]; // 下标从0开始，表示关系矩阵
void init() {
    for (int i = 0, u, v; i < m; i++)
        cin >> u >> v, d[u][v] = 1;
}
void floyd() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k]) // d[i][k] && d[k][j] => d[i][j] = 1;
                d[i] |= d[k]; // 代替一层循环
}
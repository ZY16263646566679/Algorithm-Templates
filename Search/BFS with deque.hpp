// BFS 与双端队列——解决边权为 0 或 1 的特殊图问题
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

// 例题：https://www.luogu.com.cn/problem/P4667
const int N = 505;
const int dx[4] {1, 1, -1, -1}, dy[4] {1, -1, 1, -1};
int n, m, dis[N][N]; // dis[x][y] 表示从起点到 (x, y) 的最短距离
bool g[N][N]; // g[i][j]: s[i][j] == '/'
deque<pii> q;

int bfs() {
    memset(dis, 0x3f, sizeof(dis));
    q.push_back({0, 0});
    dis[0][0] = 0;
    while (q.size()) {
        auto [x, y] = q.front(); q.pop_front();
        if (x == n && y == m)
            return dis[n][m];
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            int d = dx[i] != dy[i] ^ g[min(x, nx)][min(y, ny)];
            if (0 <= nx && nx <= n && 0 <= ny && ny <= m && dis[x][y] + d < dis[nx][ny]) {
                dis[nx][ny] = dis[x][y] + d;
                d ? q.push_back({nx, ny}) : q.push_front({nx, ny});
            }
        }
    }
    return -1;
}
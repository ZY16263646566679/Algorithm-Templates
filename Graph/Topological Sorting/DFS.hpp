// 用DFS输出所有的拓扑序
#include <bits/stdc++.h>
using namespace std;

const int N = 25;
// 节点下标从0开始
int n, topo[N], in[N]; // n节点数，topo[]拓扑序，in[]入度
bool dir[N][N], vis[N]; // dir[i][j]：i->j，vis[]访问标记

void dfs(int x, int cnt) { // 节点x的拓扑序是cnt
    topo[cnt++] = x;
    if (cnt == n) { // 一个完整的拓扑序
        for (int i = 0; i < n; i++)
            cout << topo[i] << ' ';
        cout << endl;
        return;
    }
    vis[x] = true;
    for (int i = 0; i < n; i++)
        if (dir[x][i] && !vis[i])
            in[i]--;
    for (int i = 0; i < n; i++)
        if (!in[i] && !vis[i])
            dfs(i, cnt);
    // 恢复
    for (int i = 0; i < n; i++)
        if (dir[x][i] && !vis[i])
            in[i]++;
    vis[x] = false;
}
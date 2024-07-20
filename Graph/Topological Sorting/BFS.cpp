// 用BFS输出字典序最小的拓扑序
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
// 节点下标从0开始
int n, in[N]; // n节点数，in[]入度
bool dir[N][N], inq[N]; // dir[i][j]：i->j，inq[]已入队
// 用优先队列保证字典序最小
priority_queue<int, vector<int>, greater<int>> q;

void init() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (dir[i][j]) in[j]++;
    for (int i = 0; i < n; i++)
        if (in[i] == 0)
            q.push(i), inq[i] = true;
}

bool bfs() {
    int cnt = 0;
    while (!q.empty()) { // 若队列为空后仍然有节点没有入队，说明不是DAG，拓扑排序无解
        int p = q.top();
        cout << p << ' ';
        for (int i = 0; i < n; i++)
            if (!inq[i] && dir[p][i] && in[i]) {
                inq[p] = true;
                in[i]--;
                if (!in[i]) q.push(i);
            }
        q.pop(), cnt++;
    }
    cout << endl;
    if (cnt != n) return false;
    return true;
}
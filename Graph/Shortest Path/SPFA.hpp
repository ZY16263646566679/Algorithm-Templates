// Bellman-Ford算法的优化 + SPFA的简单优化，时间复杂度O(m)，最坏情况下O(mn)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, m;
vector<pair<int, int>> e[N]; // 节点下标从1开始
int pre[N], dis[N], Neg[N]; // pre[i]：节点i的前驱节点，dis[i]：节点i到起点的距离，Neg[i]：i在队列中出现的次数（用于判断负环）
bool inq[N]; // 是否在队列中

void init() {
    memset(pre + 1, 0, n << 2);
    memset(dis + 1, 0x7f, n << 2); // 距离初始化为无穷大
    memset(Neg + 1, 0, n << 2);
    memset(inq + 1, false, n);
}

bool spfa(int s) { // 返回值表示是否存在负环
    init();
    deque<int> q;
    q.push_back(s);
    dis[s] = 0, Neg[s] = 1, inq[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        inq[u] = false;
        for (auto& [v, w] : e[u]) {
            if (dis[u] + w >= dis[v]) continue; // 无法更新距离
            dis[v] = dis[u] + w;
            pre[v] = u;            // 记录路径
            if (!inq[v]) {
                q.push_back(v);
                inq[v] = true;
                Neg[v]++;
                if (Neg[v] > n) return true; // 存在负环
            }
        }
    }
    return false;
}

/** LLL出队优化（Large Label Last）+ SLF入队优化（Small Lebal First）
 * q.size()类型是size_t(unsigned long long)，要转换成有符数，否则无法比较负数
 */
bool spfa(int s) { // 返回值表示是否存在负环
    init();
    deque<int> q;
    q.push_back(s);
    dis[s] = 0, Neg[s] = 1, inq[s] = true;
    long long x = 0; // 队列中距离的总和
    while (!q.empty()) {
        while (dis[q.front()] * (long long)q.size() > x) // LLL
            q.push_back(q.front()), q.pop_front();
        int u = q.front(); q.pop_front();
        x -= dis[u];
        inq[u] = false;
        for (auto& [v, w] : e[u]) {
            if (dis[u] + w >= dis[v]) continue; // 无法更新距离
            dis[v] = dis[u] + w;
            pre[v] = u;
            if (!inq[v]) {
                if (dis[v] < dis[q.front()]) q.push_front(v); // SLF
                else q.push_back(v);
                x += dis[v];
                inq[v] = true;
                Neg[v]++;
                if (Neg[v] > n) return true; // 存在负环
            }
        }
    }
    return false;
}
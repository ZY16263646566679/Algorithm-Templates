// Hierholzer 算法求欧拉路径（一笔画）
#include <bits/stdc++.h>
using namespace std;

/**
 * —— 判断条件（前提是连通图） ——
 * 对于无向图：
 * 1) 存在0个奇点，存在欧拉回路；
 * 2) 存在2个奇点，则为欧拉路径的起点和终点；
 * 对于有向图，出度记为1，入度记为-1，总和为度数：
 * 1) 所有点的度数都是0，则存在欧拉回路；
 * 2) 一个点的度数是1，一个点的度数是-1，则存在欧拉路径，起点是度数为1的点，终点是度数为-1的点；
 */

const int N = 1e5 + 5;
int n, m, deg[N], del[N]; // 记录度数、删边后的第一个下标
vector<int> e[N];
stack<int> st; // 最后倒序输出

void dfs(int u) {
    int len = e[u].size();
    while (del[u] < len)
        dfs(e[u][del[u]++]);
    st.push(u); // 让遍历完出边的点先入栈，并最后输出，否则会有部分点无法到达
}

int get_start() {
    // 求字典序最短的欧拉路径
    // for (int i = 1; i <= n; i++)
    //     sort(e[i].begin(), e[i].end());
    int s = 1, c[2] {}; // 记录度数
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) continue;
        if (abs(deg[i]) > 1 || ++c[deg[i] == 1] > 1)
            return 0;
        if (deg[i] == 1) s = i;
    }
    return c[-1] == c[1] ? s : 0;
}

/**
 * 更加简洁的写法：
 * 用堆来存储边：priority_queue<int, vi, greater<>> e[N]
 * 然后从堆中取最小值来保证字典序最小
 */
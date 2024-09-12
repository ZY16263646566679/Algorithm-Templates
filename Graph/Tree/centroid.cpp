// 树的重心——maxsub[]中的最小值对应的节点，可能不唯一
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, num[N], maxsub[N]; // n：节点数，num[i]：以i为根节点的树的节点数量，maxsub[i]：节点i的最大子树的节点数量
vector<int> e[N];

void dfs(int x, int fa) { // fa -> x
    num[x] = 1; // 自己
    for (int v : e[x]) {
        if (v == fa) continue; // 跳过父节点
        dfs(v, x);
        num[x] += num[v];
        if (maxsub[x] < num[v]) maxsub[x] =  num[v];
    }
    if (maxsub[x] < n - num[x]) maxsub[x] = n - num[x]; // 取最大值
}
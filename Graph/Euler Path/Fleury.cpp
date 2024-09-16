// Fleury 算法求欧拉路径（一笔画），实现方法复杂，实用性不高
#include <bits/stdc++.h>
using namespace std;

int ans[200], top, n, m, mp[200][200];

void dfs(int x) {
    top++;
    ans[top] = x;
    for (int i = 1; i <= n; i++)
        if(mp[x][i]) {
            mp[x][i] = mp[i][x] = 0; // 删除此边
            dfs(i);
            break;
        }
}

void fleury(int x) {
    int brige, i;
    top = 1;
    ans[top] = x; // 将起点放入Euler路径中
    while (top >= 0) {
        brige = 0;
        for (i = 1; i <= n; i++) // 试图搜索一条边不是割边（桥）
            if (mp[ans[top]][i]) { // 存在一条可以扩展的边
                brige = 1;
                break;
            }
        if (!brige) { // 如果没有点可以扩展，输出并出栈
            if (ans[top])
                printf("%d ", ans[top]);
            top--;
        } else { // 否则继续搜索欧拉路径
            top--; // 为了回溯
            dfs(ans[top + 1]);
        }
    }
}

int main() {
    int x, y, deg, num, start, i, j;
    scanf("%d%d", &n, &m);
    memset(mp, 0, sizeof(mp));
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        mp[x][y] = 1;
        mp[y][x] = 1;
    }
    num = 0;
    start = 1; // 这里初始化为1
    for (i = 1; i <= n; i++) {
        deg = 0;
        for (j = 1; j <= n; j++)
            deg += mp[i][j];
        if (deg % 2 == 1) {
            start = i;
            num++;
        }
    }
    if (num == 0 || num == 2) {
        fleury(start);
    } else {
        puts("no Euler path");
    }
    return 0;
}
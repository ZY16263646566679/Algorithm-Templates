// 可撤销并查集
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, s[N], sz[N], st[N], top; // 下标从1开始，st记录合并的集合，sz记录集合的秩（不是大小）。

void init() {
    top = 0;
    for (int i = 1; i <= n; i++)
        s[i] = i, sz[i] = 1;
}

int find(int x) {
    return x == s[x] ? x : find(s[x]);
}

// 启发式合并——按大小合并
void merge(int x, int y) {
    int rx = find(x), ry = find(y);
    if (sz[rx] < sz[ry]) swap(rx, ry);
    s[ry] = rx, sz[rx] += sz[ry];
    st[top++] = ry;
}

// 撤销最后一次合并
void revocate() {
    if (!top) return;
    int y = st[--top];
    sz[s[y]] -= sz[y], s[y] = y;
}

/**
 * 注意，在合并时，不可以进行路径压缩；
 * 即使 rx == ry，也要执行 sz[rx] += sz[ry]，并加到记录栈中
 * 因为撤销合并时，需要将 sz[ry] 减去
 */
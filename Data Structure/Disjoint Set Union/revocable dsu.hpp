// 可撤销并查集
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, s[N], sz[N], top; // 下标从1开始
pair<int, int> st[N];

void init() {
    top = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    return x == s[x] ? x : find(s[x]);
}

// 启发式合并——按大小合并
void merge(int x, int y) {
    int rx = find(x), ry = find(y);
    if (sz[rx] < sz[ry]) swap(rx, ry);
    s[ry] = rx;
    sz[rx] += sz[ry];
    st[top++] = make_pair(rx, ry);
}

// 撤销最后一次合并
void revocate() {
    if (!top) return;
    auto [rx, ry] = st[--top];
    sz[rx] -= sz[ry];
    s[ry] = ry;
}
// 并查集
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
int s[N], d[N];

void init() {
    for (int i = 1; i <= N; i++) {
        s[i] = i;
        // d[i] = 0;
    }
}

int find(int x) {
    if (x != s[x]) {
        // int t = s[x];
        s[x] = find(s[x]);
        // d[x] += d[t];
    }
    return s[x];
}

bool merge(int x, int y, int w = 0) {
    int rootx = find(x), rooty = find(y);
    // 带权
    // if (rootx == rooty) {
    //     if (d[x] - d[y] != w)
    //         return false;
    // } else {
    //     s[rootx] = rooty;
    //     d[rootx] = d[y] + w - d[x];
    // }
    // return true

    // 不带权
    s[rootx] = rooty;
}

class dsu { // disjoint set union
public:
    vector<int> parents;
    vector<int> sizes;
    dsu(int n) {
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        sizes.resize(n, 1);
    }
    int root(int v) {
        return parents[v] == v ? v : parents[v] = root(parents[v]);
    }
    bool join(int u, int v) { // 返回是否是在同一集合
        int a = root(u), b = root(v);
        if (a == b)
            return false;
        if (sizes[a] > sizes[b])
            swap(a, b);
        parents[a] = b; // b集合大于a集合，a合并到b上
        sizes[b] += sizes[a];
        return true;
    }
    int size(int v) { // 获取集合的大小
        return sizes[root(v)];
    }
};
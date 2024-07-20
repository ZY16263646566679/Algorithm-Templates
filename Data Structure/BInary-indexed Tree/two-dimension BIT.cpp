// 二维树状数组（树状数组套树状数组）
#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) ((x) & -(x))

const int N = 1e3 + 5;
int m, n, t[N][N];

void add(int x, int y, int d) {
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            t[i][j] += d;
}

int sum(int x, int y) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += t[i][j];
    return res;
}
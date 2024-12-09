// 单调队列优化 DP
#include <bits/stdc++.h>
using namespace std;

// 适用于 f[i] = max{ f[j] + b[j] + a[i] }, i - r <= j <= i - l
// 例题：https://www.luogu.com.cn/problem/P1725
const int N = 2e5 + 5;
int n, l, r, a[N], ans = INT_MIN;
int q[N], h, t;

void solve() {
    for (int i = 1; i <= n; i++) {
        while (t > h && q[h] < i - r) h++;
        while (t > h && a[q[t - 1]] <= a[i - l]) t--;
        if (i >= l & a[i - l] != INT_MIN) q[t++] = i - l;
        a[i] = t > h ? a[q[h]] + a[i] : INT_MIN;
        if (i + r > n) ans = max(ans, a[i]);
    }
}
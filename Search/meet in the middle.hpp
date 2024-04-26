// 折半搜索
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * 适用问题：每个元素有 k 种状态，总共有 n^k 种状态
 * 例题链接：https://www.luogu.com.cn/problem/P4799
 */
const int N = 45;
ll n, m, a[N], ans;
vector<ll> suma, sumb; // 将所有可能的和放到两个数组里

void dfs(int l, int r, ll s, vector<ll>& sum) {
    if (s > m) return; // 剪枝
    if (l > r) {
        sum.emplace_back(s);
        return;
    }
    dfs(l + 1, r, s + a[l], sum);
    dfs(l + 1, r, s, sum);
}

ll solve() {
    dfs(0, n / 2, 0, suma);
    dfs(n / 2 + 1, n - 1, 0, sumb);
    sort(sumb.begin(), sumb.end()); // 合并
    ll ans = 0;
    for (ll& x : suma) // 统计方案数
        ans += upper_bound(sumb.begin(), sumb.end(), m - x) - sumb.begin();
    return ans;
}
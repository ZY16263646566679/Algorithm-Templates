// 反素数
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

// 求解约数个数为n的最小数
ll n, res = INF;
int prime[16] { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 }; // prime[15]：第15个素数
// 法一：深度优先搜索
void dfs(int p, ll val, int num, int up) { // 该第p个素数，目前的值为val，约数个数为num，第p个素数最多up个
    for (ll i = 1, x = prime[p]; i <= up && INF / x >= val; i++, x *= prime[p]) {
        if (num * (i + 1) == n) {
            if (val * x < res) res = val * x;
            break;
        }
        if (p < 15) dfs(p + 1, val * x, num * (i + 1), up);
    }
}

ll calc() {
    if (n == 1) return 1;
    dfs(1, 1, 1, 61);
    return res;
}

// 法二：动态规划
ll f[1001]; // f[j]：约数个数为j的最小整数
void dp() {
    memset(f, 0x3f, sizeof(f)); // 初始化为无穷大
    f[1] = 1;
    for (int i = 1; i <= 15; i++) // 枚举素数
        for (int j = 1000; j >= 1; j--) { // 滚动数组优化：倒序dp
            ll p = 1;
            for (int k = 0; k <= 61; k++) {
                if (j * (k + 1) > 1000 || INF / prime[i] < p) break;
                if (k > 0) p *= prime[i];
                if (f[j * (k + 1)] / p >= f[j])
                    f[j * (k + 1)] = p * f[j];
            }
        }
}

/**
 * 反素数
 * 记g(x)为x的约数个数
 * 如果对于任意i属于[1, x)，满足g(i) < g(x)，称x为反素数
 */

// 求解不超过n的最大反素数
ll n, maxn = -1, ans = -1;
ll get(ll m, ll f, ll t, ll pr) { // f为当前质数的编号，当前指数小于pr，t为当前约数的个数，m表示当前可能成为最优解的数
    if (t > maxn || t == maxn && m < ans) // 更新最优解
        ans = m, maxn = t;
    for (ll i = 0, j = m, nt = 0; i++ < pr;) { // i表示的是当前正在搜索的指数
        if (n / j < prime[f]) break; // 若不满足条件就跳出循环（j表示的是当前的m）
        nt = t * (i + 1), j *= prime[f]; // 更新新数以及它的因子个数
        if (j <= n) get(j, f + 1, nt, i); // 若j（即当前的m）在区间[1,n]内就继续搜索
    }
    return ans;
}